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
struct s_zstate {int dummy; } ;
typedef  int /*<<< orphan*/  code_int ;

/* Variables and functions */
 scalar_t__ EOF ; 
 scalar_t__ ent ; 
 scalar_t__ fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fp ; 
 int /*<<< orphan*/  free (struct s_zstate*) ; 
 int /*<<< orphan*/  out_count ; 
 int output (struct s_zstate*,int /*<<< orphan*/ ) ; 
 char zmode ; 

__attribute__((used)) static int
zclose(void *cookie)
{
	struct s_zstate *zs;
	int rval;

	zs = cookie;
	if (zmode == 'w') {		/* Put out the final code. */
		if (output(zs, (code_int) ent) == -1) {
			(void)fclose(fp);
			free(zs);
			return (-1);
		}
		out_count++;
		if (output(zs, (code_int) - 1) == -1) {
			(void)fclose(fp);
			free(zs);
			return (-1);
		}
	}
	rval = fclose(fp) == EOF ? -1 : 0;
	free(zs);
	return (rval);
}