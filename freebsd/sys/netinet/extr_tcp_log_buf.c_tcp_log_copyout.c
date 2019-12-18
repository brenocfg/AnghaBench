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
struct sockopt {int /*<<< orphan*/ * sopt_td; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (void*,void*,size_t) ; 
 int copyout (void*,void*,size_t) ; 

__attribute__((used)) static inline int
tcp_log_copyout(struct sockopt *sopt, void *src, void *dst, size_t len)
{

	if (sopt->sopt_td != NULL)
		return (copyout(src, dst, len));
	bcopy(src, dst, len);
	return (0);
}