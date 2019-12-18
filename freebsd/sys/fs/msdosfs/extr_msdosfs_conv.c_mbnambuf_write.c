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
struct mbnambuf {size_t nb_len; int nb_last_id; char* nb_buf; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENAMETOOLONG ; 
 size_t MAXNAMLEN ; 
 int WIN_CHARS ; 
 size_t WIN_MAXLEN ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int /*<<< orphan*/  printf (char*,size_t,...) ; 
 size_t strlen (char*) ; 

int
mbnambuf_write(struct mbnambuf *nbp, char *name, int id)
{
	char *slot;
	size_t count, newlen;

	if (nbp->nb_len != 0 && id != nbp->nb_last_id - 1) {
#ifdef MSDOSFS_DEBUG
		printf("msdosfs: non-decreasing id: id %d, last id %d\n",
		    id, nbp->nb_last_id);
#endif
		return (EINVAL);
	}

	/* Will store this substring in a WIN_CHARS-aligned slot. */
	slot = &nbp->nb_buf[id * WIN_CHARS];
	count = strlen(name);
	newlen = nbp->nb_len + count;
	if (newlen > WIN_MAXLEN || newlen > MAXNAMLEN) {
#ifdef MSDOSFS_DEBUG
		printf("msdosfs: file name length %zu too large\n", newlen);
#endif
		return (ENAMETOOLONG);
	}

	/* Shift suffix upwards by the amount length exceeds WIN_CHARS. */
	if (count > WIN_CHARS && nbp->nb_len != 0) {
		if ((id * WIN_CHARS + count + nbp->nb_len) >
		    sizeof(nbp->nb_buf))
			return (ENAMETOOLONG);

		memmove(slot + count, slot + WIN_CHARS, nbp->nb_len);
	}

	/* Copy in the substring to its slot and update length so far. */
	memcpy(slot, name, count);
	nbp->nb_len = newlen;
	nbp->nb_last_id = id;

	return (0);
}