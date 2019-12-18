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
struct __wrusage {int dummy; } ;
typedef  int /*<<< orphan*/  siginfo_t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  idtype_t ;
typedef  int /*<<< orphan*/  id_t ;

/* Variables and functions */
 size_t INTERPOS_wait6 ; 
 scalar_t__* __libc_interposing ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,struct __wrusage*,int /*<<< orphan*/ *) ; 

pid_t
wait6(idtype_t idtype, id_t id, int *status, int options, struct __wrusage *ru,
    siginfo_t *infop)
{

	return (((pid_t (*)(idtype_t, id_t, int *, int, struct __wrusage *,
	    siginfo_t *))__libc_interposing[INTERPOS_wait6])(idtype, id,
	    status, options, ru, infop));
}