#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int off_t ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int o_data; } ;
typedef  TYPE_1__ PLAN ;
typedef  TYPE_2__ OPTION ;

/* Variables and functions */
 int /*<<< orphan*/  FTS_NOSTAT ; 
 int QUAD_MAX ; 
 scalar_t__ divsize ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,char*) ; 
 int find_parsenum (TYPE_1__*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ftsoptions ; 
 char* nextarg (TYPE_2__*,char***) ; 
 TYPE_1__* palloc (TYPE_2__*) ; 

PLAN *
c_size(OPTION *option, char ***argvp)
{
	char *size_str;
	PLAN *new;
	char endch;
	off_t scale;

	size_str = nextarg(option, argvp);
	ftsoptions &= ~FTS_NOSTAT;

	new = palloc(option);
	endch = 'c';
	new->o_data = find_parsenum(new, option->name, size_str, &endch);
	if (endch != '\0') {
		divsize = 0;

		switch (endch) {
		case 'c':                       /* characters */
			scale = 0x1LL;
			break;
		case 'k':                       /* kilobytes 1<<10 */
			scale = 0x400LL;
			break;
		case 'M':                       /* megabytes 1<<20 */
			scale = 0x100000LL;
			break;
		case 'G':                       /* gigabytes 1<<30 */
			scale = 0x40000000LL;
			break;
		case 'T':                       /* terabytes 1<<40 */
			scale = 0x10000000000LL;
			break;
		case 'P':                       /* petabytes 1<<50 */
			scale = 0x4000000000000LL;
			break;
		default:
			errx(1, "%s: %s: illegal trailing character",
				option->name, size_str);
			break;
		}
		if (new->o_data > QUAD_MAX / scale)
			errx(1, "%s: %s: value too large",
				option->name, size_str);
		new->o_data *= scale;
	}
	return new;
}