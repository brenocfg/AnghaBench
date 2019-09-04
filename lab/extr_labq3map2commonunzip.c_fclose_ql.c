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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int fclose (int /*<<< orphan*/ *) ; 
 int xor_max_pos ; 
 int /*<<< orphan*/ ** xored_open_files ; 

int fclose_ql (FILE* stream) {
    int ret;
	int i;

	//printf("close %p ", stream);
	//for (i = 0;  i < MAX_FILE_HANDLES;  i++) {
	for (i = 0;  i <= xor_max_pos;  i++) {
		if (xored_open_files[i] == stream) {
			xored_open_files[i] = NULL;
			if (i == xor_max_pos) {
				xor_max_pos--;
			}
			//printf("xor");
			break;
		}
	}
	//printf("\n");

    ret = fclose((FILE *)stream);
    return ret;
}