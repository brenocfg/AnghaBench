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
typedef  int u_int ;
struct execsw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct execsw const** execsw ; 
 int /*<<< orphan*/  free (struct execsw const**,int /*<<< orphan*/ ) ; 
 struct execsw** malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
exec_register(const struct execsw *execsw_arg)
{
	const struct execsw **es, **xs, **newexecsw;
	u_int count = 2;	/* New slot and trailing NULL */

	if (execsw)
		for (es = execsw; *es; es++)
			count++;
	newexecsw = malloc(count * sizeof(*es), M_TEMP, M_WAITOK);
	xs = newexecsw;
	if (execsw)
		for (es = execsw; *es; es++)
			*xs++ = *es;
	*xs++ = execsw_arg;
	*xs = NULL;
	if (execsw)
		free(execsw, M_TEMP);
	execsw = newexecsw;
	return (0);
}