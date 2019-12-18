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
typedef  size_t u_int ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  input_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ ** paths ; 
 int /*<<< orphan*/ * tryopen (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static int32_t
input_fopen(const char *fname)
{
	FILE *fp;
	u_int p;

	if (fname[0] == '/' || fname[0] == '.' || fname[0] == '~') {
		if ((fp = tryopen(NULL, fname)) != NULL) {
			input_new(fp, NULL, fname);
			return (0);
		}

	} else {

		for (p = 0; paths[p] != NULL; p++)
			if ((fp = tryopen(paths[p], fname)) != NULL) {
				input_new(fp, paths[p], fname);
				return (0);
			}
	}

	warnx("cannot open '%s'", fname);
	return (-1);
}