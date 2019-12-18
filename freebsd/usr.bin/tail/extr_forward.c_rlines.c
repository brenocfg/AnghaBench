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
struct stat {scalar_t__ st_size; } ;
struct mapinfo {char* start; scalar_t__ mapoff; scalar_t__ maxoff; int /*<<< orphan*/  maplen; int /*<<< orphan*/  fd; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int fseeko (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ierr (char const*) ; 
 scalar_t__ maparound (struct mapinfo*,scalar_t__) ; 
 scalar_t__ mapprint (struct mapinfo*,scalar_t__,scalar_t__) ; 
 scalar_t__ munmap (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rlines(FILE *fp, const char *fn, off_t off, struct stat *sbp)
{
	struct mapinfo map;
	off_t curoff, size;
	int i;

	if (!(size = sbp->st_size))
		return;
	map.start = NULL;
	map.fd = fileno(fp);
	map.mapoff = map.maxoff = size;

	/*
	 * Last char is special, ignore whether newline or not. Note that
	 * size == 0 is dealt with above, and size == 1 sets curoff to -1.
	 */
	curoff = size - 2;
	while (curoff >= 0) {
		if (curoff < map.mapoff && maparound(&map, curoff) != 0) {
			ierr(fn);
			return;
		}
		for (i = curoff - map.mapoff; i >= 0; i--)
			if (map.start[i] == '\n' && --off == 0)
				break;
		/* `i' is either the map offset of a '\n', or -1. */
		curoff = map.mapoff + i;
		if (i >= 0)
			break;
	}
	curoff++;
	if (mapprint(&map, curoff, size - curoff) != 0) {
		ierr(fn);
		exit(1);
	}

	/* Set the file pointer to reflect the length displayed. */
	if (fseeko(fp, sbp->st_size, SEEK_SET) == -1) {
		ierr(fn);
		return;
	}
	if (map.start != NULL && munmap(map.start, map.maplen)) {
		ierr(fn);
		return;
	}
}