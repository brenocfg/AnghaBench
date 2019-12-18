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
typedef  int /*<<< orphan*/  val ;
struct sockopt {int sopt_level; int sopt_name; int* sopt_val; int sopt_valsize; } ;
struct socket {int /*<<< orphan*/  so_vnet; } ;
typedef  int /*<<< orphan*/  sopt ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct sockopt*,int) ; 
 int sosetopt (struct socket*,struct sockopt*) ; 

__attribute__((used)) static int
nb_setsockopt_int(struct socket *so, int level, int name, int val)
{
	struct sockopt sopt;
	int error;

	bzero(&sopt, sizeof(sopt));
	sopt.sopt_level = level;
	sopt.sopt_name = name;
	sopt.sopt_val = &val;
	sopt.sopt_valsize = sizeof(val);
	CURVNET_SET(so->so_vnet);
	error = sosetopt(so, &sopt);
	CURVNET_RESTORE();
	return error;
}