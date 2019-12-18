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
typedef  char uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* scalloc (int,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static uint8_t *concat_strings(char **glyphs, int max) {
    uint8_t *output = scalloc(max + 1, 4);
    uint8_t *walk = output;
    for (int c = 0; c < max; c++) {
        printf("at %c\n", glyphs[c][0]);
        /* if the first byte is 0, this has to be UCS2 */
        if (glyphs[c][0] == '\0') {
            memcpy(walk, glyphs[c], 2);
            walk += 2;
        } else {
            strcpy((char *)walk, glyphs[c]);
            walk += strlen(glyphs[c]);
        }
    }
    printf("output = %s\n", output);
    return output;
}