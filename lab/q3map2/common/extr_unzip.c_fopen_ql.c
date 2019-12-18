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
 int MAX_FILE_HANDLES ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 
 int /*<<< orphan*/  fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ *) ; 
 int xor_max_pos ; 
 int /*<<< orphan*/ ** xored_open_files ; 

FILE* fopen_ql (const char* filename, const char* mode) {
    FILE* file = NULL;

    if ((filename!=NULL) && (mode != NULL))
        file = fopen(filename, mode);

	if (file) {
		int i;
		char magic[4];
		int useXor = 1;
		//int foundPlace = 0;

		fread(magic, 1, 4, file);
		if (magic[0] == 'P'  &&  magic[1] == 'K'  &&  magic[2] == '\x03') {
			useXor = 0;
		}
		fseek(file, 0, SEEK_SET);
		if (!useXor) {
			//printf("opened %p not xored\n", file);
			return file;
		}
		for (i = 0;  i < MAX_FILE_HANDLES;  i++) {
		//for (i = 0;  i <= xor_max_pos;  i++) {
			// assuming we don't open files more than once
			if (xored_open_files[i] == NULL) {
				xored_open_files[i] = file;
				//printf("opend %p xored\n", file);
				if (i > xor_max_pos) {
					xor_max_pos = i;
				}
				return file;
				break;
			}
		}
		printf("error couldn't find a spot for %p\n", file);
		return NULL; //exit
	}

    return file;
}