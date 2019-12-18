#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vdd {TYPE_1__* pathtbl; } ;
struct isoent {size_t id_len; int /*<<< orphan*/ * identifier; TYPE_2__* parent; int /*<<< orphan*/  dir_location; } ;
struct archive_write {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dir_number; } ;
struct TYPE_3__ {int cnt; struct isoent** sorted; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  set_num_711 (unsigned char*,unsigned char) ; 
 int /*<<< orphan*/  set_num_721 (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_num_722 (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_num_731 (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_num_732 (unsigned char*,int /*<<< orphan*/ ) ; 
 unsigned char* wb_buffptr (struct archive_write*) ; 
 int wb_consume (struct archive_write*,int) ; 
 size_t wb_remaining (struct archive_write*) ; 

__attribute__((used)) static int
_write_path_table(struct archive_write *a, int type_m, int depth,
    struct vdd *vdd)
{
	unsigned char *bp, *wb;
	struct isoent **ptbl;
	size_t wbremaining;
	int i, r, wsize;

	if (vdd->pathtbl[depth].cnt == 0)
		return (0);

	wsize = 0;
	wb = wb_buffptr(a);
	wbremaining = wb_remaining(a);
	bp = wb - 1;
	ptbl = vdd->pathtbl[depth].sorted;
	for (i = 0; i < vdd->pathtbl[depth].cnt; i++) {
		struct isoent *np;
		size_t len;

		np = ptbl[i];
		if (np->identifier == NULL)
			len = 1; /* root directory */
		else
			len = np->id_len;
		if (wbremaining - ((bp+1) - wb) < (len + 1 + 8)) {
			r = wb_consume(a, (bp+1) - wb);
			if (r < 0)
				return (r);
			wb = wb_buffptr(a);
			wbremaining = wb_remaining(a);
			bp = wb -1;
		}
		/* Length of Directory Identifier */
		set_num_711(bp+1, (unsigned char)len);
		/* Extended Attribute Record Length */
		set_num_711(bp+2, 0);
		/* Location of Extent */
		if (type_m)
			set_num_732(bp+3, np->dir_location);
		else
			set_num_731(bp+3, np->dir_location);
		/* Parent Directory Number */
		if (type_m)
			set_num_722(bp+7, np->parent->dir_number);
		else
			set_num_721(bp+7, np->parent->dir_number);
		/* Directory Identifier */
		if (np->identifier == NULL)
			bp[9] = 0;
		else
			memcpy(&bp[9], np->identifier, len);
		if (len & 0x01) {
			/* Padding Field */
			bp[9+len] = 0;
			len++;
		}
		wsize += 8 + (int)len;
		bp += 8 + len;
	}
	if ((bp + 1) > wb) {
		r = wb_consume(a, (bp+1)-wb);
		if (r < 0)
			return (r);
	}
	return (wsize);
}