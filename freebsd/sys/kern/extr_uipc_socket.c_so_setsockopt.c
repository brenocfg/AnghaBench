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
struct sockopt {int sopt_level; int sopt_name; size_t sopt_valsize; int /*<<< orphan*/ * sopt_td; void* sopt_val; int /*<<< orphan*/  sopt_dir; } ;
struct socket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOPT_SET ; 
 int sosetopt (struct socket*,struct sockopt*) ; 

int
so_setsockopt(struct socket *so, int level, int optname, void *optval,
    size_t optlen)
{
	struct sockopt sopt;

	sopt.sopt_level = level;
	sopt.sopt_name = optname;
	sopt.sopt_dir = SOPT_SET;
	sopt.sopt_val = optval;
	sopt.sopt_valsize = optlen;
	sopt.sopt_td = NULL;
	return (sosetopt(so, &sopt));
}