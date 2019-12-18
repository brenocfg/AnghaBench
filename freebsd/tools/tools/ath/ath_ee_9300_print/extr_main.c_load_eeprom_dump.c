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
typedef  unsigned int uint16_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
load_eeprom_dump(const char *file, uint16_t *buf)
{
	unsigned int r[8];
	FILE *fp;
	char b[1024];
	int i;

	fp = fopen(file, "r");
	if (!fp)
		err(1, "fopen");

	while (!feof(fp)) {
		if (fgets(b, 1024, fp) == NULL)
			break;
		if (feof(fp))
			break;
		if (strlen(b) > 0)
			b[strlen(b)-1] = '\0';
		if (strlen(b) == 0)
			break;
		sscanf(b, "%x: %x %x %x %x %x %x %x %x\n",
		    &i, &r[0], &r[1], &r[2], &r[3], &r[4],
		    &r[5], &r[6], &r[7]);
		buf[i++] = r[0];
		buf[i++] = r[1];
		buf[i++] = r[2];
		buf[i++] = r[3];
		buf[i++] = r[4];
		buf[i++] = r[5];
		buf[i++] = r[6];
		buf[i++] = r[7];
	}
	fclose(fp);
}