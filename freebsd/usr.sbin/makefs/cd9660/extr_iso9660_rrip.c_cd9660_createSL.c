#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int* version; int* length; } ;
struct TYPE_10__ {char* flags; char* component; TYPE_2__ h; } ;
struct TYPE_11__ {TYPE_3__ SL; } ;
struct TYPE_12__ {TYPE_4__ rr_entry; } ;
struct ISO_SUSP_ATTRIBUTES {TYPE_5__ attr; } ;
struct TYPE_13__ {int /*<<< orphan*/  head; TYPE_1__* node; } ;
typedef  TYPE_6__ cd9660node ;
struct TYPE_8__ {char* symlink; } ;

/* Variables and functions */
 char SL_FLAGS_CONTINUE ; 
 char SL_FLAGS_CURRENT ; 
 void* SL_FLAGS_NONE ; 
 char SL_FLAGS_PARENT ; 
 char SL_FLAGS_ROOT ; 
 int /*<<< orphan*/  SUSP_ENTRY_RRIP_SL ; 
 int /*<<< orphan*/  SUSP_LOC_ENTRY ; 
 int /*<<< orphan*/  SUSP_TYPE_RRIP ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ISO_SUSP_ATTRIBUTES*,int /*<<< orphan*/ ) ; 
 struct ISO_SUSP_ATTRIBUTES* cd9660node_susp_create_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  rr_ll ; 

void
cd9660_createSL(cd9660node *node)
{
	struct ISO_SUSP_ATTRIBUTES* current;
	int path_count, dir_count, done, i, j, dir_copied;
	char temp_cr[255];
	char temp_sl[255]; /* used in copying continuation entry*/
	char* sl_ptr;

	sl_ptr = node->node->symlink;

	done = 0;
	path_count = 0;
	dir_count = 0;
	dir_copied = 0;
	current = cd9660node_susp_create_node(SUSP_TYPE_RRIP,
	    SUSP_ENTRY_RRIP_SL, "SL", SUSP_LOC_ENTRY);

	current->attr.rr_entry.SL.h.version[0] = 1;
	current->attr.rr_entry.SL.flags[0] = SL_FLAGS_NONE;

	if (*sl_ptr == '/') {
		temp_cr[0] = SL_FLAGS_ROOT;
		temp_cr[1] = 0;
		memcpy(current->attr.rr_entry.SL.component + path_count,
		    temp_cr, 2);
		path_count += 2;
		sl_ptr++;
	}

	for (i = 0; i < (dir_count + 2); i++)
		temp_cr[i] = '\0';

	while (!done) {
		while ((*sl_ptr != '/') && (*sl_ptr != '\0')) {
			dir_copied = 1;
			if (*sl_ptr == '.') {
				if ((*(sl_ptr + 1) == '/') || (*(sl_ptr + 1)
				     == '\0')) {
					temp_cr[0] = SL_FLAGS_CURRENT;
					sl_ptr++;
				} else if(*(sl_ptr + 1) == '.') {
					if ((*(sl_ptr + 2) == '/') ||
					    (*(sl_ptr + 2) == '\0')) {
						temp_cr[0] = SL_FLAGS_PARENT;
						sl_ptr += 2;
					}
				} else {
					temp_cr[dir_count+2] = *sl_ptr;
					sl_ptr++;
					dir_count++;
				}
			} else {
				temp_cr[dir_count + 2] = *sl_ptr;
				sl_ptr++;
				dir_count++;
			}
		}

		if ((path_count + dir_count) >= 249) {
			current->attr.rr_entry.SL.flags[0] |= SL_FLAGS_CONTINUE;

			j = 0;

			if (path_count <= 249) {
				while(j != (249 - path_count)) {
					temp_sl[j] = temp_cr[j];
					j++;
				}
				temp_sl[0] = SL_FLAGS_CONTINUE;
				temp_sl[1] = j - 2;
				memcpy(
				    current->attr.rr_entry.SL.component +
					path_count,
				    temp_sl, j);
			}

			path_count += j;
			current->attr.rr_entry.SL.h.length[0] = path_count + 5;
			TAILQ_INSERT_TAIL(&node->head, current, rr_ll);
			current= cd9660node_susp_create_node(SUSP_TYPE_RRIP,
			       SUSP_ENTRY_RRIP_SL, "SL", SUSP_LOC_ENTRY);
			current->attr.rr_entry.SL.h.version[0] = 1;
			current->attr.rr_entry.SL.flags[0] = SL_FLAGS_NONE;

			path_count = 0;

			if (dir_count > 2) {
				while (j != dir_count + 2) {
					current->attr.rr_entry.SL.component[
					    path_count + 2] = temp_cr[j];
					j++;
					path_count++;
				}
				current->attr.rr_entry.SL.component[1]
				    = path_count;
				path_count+= 2;
			} else {
				while(j != dir_count) {
					current->attr.rr_entry.SL.component[
					    path_count+2] = temp_cr[j];
					j++;
					path_count++;
				}
			}
		} else {
			if (dir_copied == 1) {
				temp_cr[1] = dir_count;
				memcpy(current->attr.rr_entry.SL.component +
					path_count,
				    temp_cr, dir_count + 2);
				path_count += dir_count + 2;
			}
		}

		if (*sl_ptr == '\0') {
			done = 1;
			current->attr.rr_entry.SL.h.length[0] = path_count + 5;
			TAILQ_INSERT_TAIL(&node->head, current, rr_ll);
		} else {
			sl_ptr++;
			dir_count = 0;
			dir_copied = 0;
			for(i = 0; i < 255; i++) {
				temp_cr[i] = '\0';
			}
		}
	}
}