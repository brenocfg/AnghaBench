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
typedef  int /*<<< orphan*/  version ;
struct stat {int st_size; } ;
struct moduledir {int* d_hints; int d_flags; int d_hintsz; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int LINKER_HINTS_MAX ; 
 int LINKER_HINTS_VERSION ; 
 int MDIR_NOHINTS ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int* malloc (int) ; 
 char* moduledir_fullpath (struct moduledir*,char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,int*,int) ; 
 scalar_t__ stat (char*,struct stat*) ; 

__attribute__((used)) static void
moduledir_readhints(struct moduledir *mdp)
{
	struct stat	st;
	char	*path;
	int		fd, size, version;

	if (mdp->d_hints != NULL || (mdp->d_flags & MDIR_NOHINTS))
		return;
	path = moduledir_fullpath(mdp, "linker.hints");
	if (stat(path, &st) != 0 ||
	  st.st_size < (ssize_t)(sizeof(version) + sizeof(int)) ||
	  st.st_size > LINKER_HINTS_MAX || (fd = open(path, O_RDONLY)) < 0) {
		free(path);
		mdp->d_flags |= MDIR_NOHINTS;
		return;
	}
	free(path);
	size = read(fd, &version, sizeof(version));
	if (size != sizeof(version) || version != LINKER_HINTS_VERSION)
		goto bad;
	size = st.st_size - size;
	mdp->d_hints = malloc(size);
	if (mdp->d_hints == NULL)
		goto bad;
	if (read(fd, mdp->d_hints, size) != size)
		goto bad;
	mdp->d_hintsz = size;
	close(fd);
	return;
bad:
	close(fd);
	free(mdp->d_hints);
	mdp->d_hints = NULL;
	mdp->d_flags |= MDIR_NOHINTS;
	return;
}