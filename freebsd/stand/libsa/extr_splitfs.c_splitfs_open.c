#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct split_file {int filesc; void** descsv; void** filesv; } ;
struct open_file {scalar_t__ f_flags; struct split_file* f_fsdata; } ;

/* Variables and functions */
 int CONF_BUF ; 
 int EISDIR ; 
 int ENOENT ; 
 int EPERM ; 
 scalar_t__ F_READ ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct split_file*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 scalar_t__ fgetstr (char*,int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ isspace (char) ; 
 void* malloc (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 void* realloc (void**,int) ; 
 int /*<<< orphan*/  split_file_destroy (struct split_file*) ; 
 scalar_t__ split_openfile (struct split_file*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 void* strdup (char*) ; 
 int strlen (char const*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static int
splitfs_open(const char *fname, struct open_file *f)
{
    char *buf, *confname, *cp;
    int	conffd;
    struct split_file *sf;
    struct stat sb;

    /* Have to be in "just read it" mode */
    if (f->f_flags != F_READ)
	return(EPERM);

    /* If the name already ends in `.split', ignore it */
    if ((cp = strrchr(fname, '.')) && (!strcmp(cp, ".split")))
	return(ENOENT);

    /* Construct new name */
    confname = malloc(strlen(fname) + 7);
    sprintf(confname, "%s.split", fname);

    /* Try to open the configuration file */
    conffd = open(confname, O_RDONLY);
    free(confname);
    if (conffd == -1)
	return(ENOENT);

    if (fstat(conffd, &sb) < 0) {
	printf("splitfs_open: stat failed\n");
	close(conffd);
	return(ENOENT);
    }
    if (!S_ISREG(sb.st_mode)) {
	printf("splitfs_open: not a file\n");
	close(conffd);
	return(EISDIR);			/* best guess */
    }

    /* Allocate a split_file structure, populate it from the config file */
    sf = malloc(sizeof(struct split_file));
    bzero(sf, sizeof(struct split_file));
    buf = malloc(CONF_BUF);
    while (fgetstr(buf, CONF_BUF, conffd) > 0) {
	cp = buf;
	while ((*cp != '\0') && (isspace(*cp) == 0))
	    cp++;
	if (*cp != '\0') {
	    *cp = '\0';
	    cp++;
	}
	while ((*cp != '\0') && (isspace(*cp) != 0))
	    cp++;
	if (*cp == '\0')
	    cp = buf;
	sf->filesc++;
	sf->filesv = realloc(sf->filesv, sizeof(*(sf->filesv)) * sf->filesc);
	sf->descsv = realloc(sf->descsv, sizeof(*(sf->descsv)) * sf->filesc);
	sf->filesv[sf->filesc - 1] = strdup(buf);
	sf->descsv[sf->filesc - 1] = strdup(cp);
    }
    free(buf);
    close(conffd);

    if (sf->filesc == 0) {
	split_file_destroy(sf);
	return(ENOENT);
    }
    errno = split_openfile(sf);
    if (errno != 0) {
	split_file_destroy(sf);
	return(ENOENT);
    }

    /* Looks OK, we'll take it */
    f->f_fsdata = sf;
    return (0);
}