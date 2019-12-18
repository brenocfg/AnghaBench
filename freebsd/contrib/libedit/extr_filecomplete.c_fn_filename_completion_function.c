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
struct dirent {char* d_name; size_t d_namlen; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 char* el_calloc (size_t,int) ; 
 int /*<<< orphan*/  el_free (char*) ; 
 char* el_realloc (char*,size_t) ; 
 char* fn_tilde_expand (char*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (char const*) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,size_t) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 
 char* strrchr (char const*,char) ; 

char *
fn_filename_completion_function(const char *text, int state)
{
	static DIR *dir = NULL;
	static char *filename = NULL, *dirname = NULL, *dirpath = NULL;
	static size_t filename_len = 0;
	struct dirent *entry;
	char *temp;
	size_t len;

	if (state == 0 || dir == NULL) {
		temp = strrchr(text, '/');
		if (temp) {
			char *nptr;
			temp++;
			nptr = el_realloc(filename, (strlen(temp) + 1) *
			    sizeof(*nptr));
			if (nptr == NULL) {
				el_free(filename);
				filename = NULL;
				return NULL;
			}
			filename = nptr;
			(void)strcpy(filename, temp);
			len = (size_t)(temp - text);	/* including last slash */

			nptr = el_realloc(dirname, (len + 1) *
			    sizeof(*nptr));
			if (nptr == NULL) {
				el_free(dirname);
				dirname = NULL;
				return NULL;
			}
			dirname = nptr;
			(void)strncpy(dirname, text, len);
			dirname[len] = '\0';
		} else {
			el_free(filename);
			if (*text == 0)
				filename = NULL;
			else {
				filename = strdup(text);
				if (filename == NULL)
					return NULL;
			}
			el_free(dirname);
			dirname = NULL;
		}

		if (dir != NULL) {
			(void)closedir(dir);
			dir = NULL;
		}

		/* support for ``~user'' syntax */

		el_free(dirpath);
		dirpath = NULL;
		if (dirname == NULL) {
			if ((dirname = strdup("")) == NULL)
				return NULL;
			dirpath = strdup("./");
		} else if (*dirname == '~')
			dirpath = fn_tilde_expand(dirname);
		else
			dirpath = strdup(dirname);

		if (dirpath == NULL)
			return NULL;

		dir = opendir(dirpath);
		if (!dir)
			return NULL;	/* cannot open the directory */

		/* will be used in cycle */
		filename_len = filename ? strlen(filename) : 0;
	}

	/* find the match */
	while ((entry = readdir(dir)) != NULL) {
		/* skip . and .. */
		if (entry->d_name[0] == '.' && (!entry->d_name[1]
		    || (entry->d_name[1] == '.' && !entry->d_name[2])))
			continue;
		if (filename_len == 0)
			break;
		/* otherwise, get first entry where first */
		/* filename_len characters are equal	  */
		if (entry->d_name[0] == filename[0]
#if HAVE_STRUCT_DIRENT_D_NAMLEN
		    && entry->d_namlen >= filename_len
#else
		    && strlen(entry->d_name) >= filename_len
#endif
		    && strncmp(entry->d_name, filename,
			filename_len) == 0)
			break;
	}

	if (entry) {		/* match found */

#if HAVE_STRUCT_DIRENT_D_NAMLEN
		len = entry->d_namlen;
#else
		len = strlen(entry->d_name);
#endif

		len = strlen(dirname) + len + 1;
		temp = el_calloc(len, sizeof(*temp));
		if (temp == NULL)
			return NULL;
		(void)snprintf(temp, len, "%s%s", dirname, entry->d_name);
	} else {
		(void)closedir(dir);
		dir = NULL;
		temp = NULL;
	}

	return temp;
}