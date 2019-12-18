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
struct ip6_pktopts {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IP6OPT ; 
 int copypktopts (struct ip6_pktopts*,struct ip6_pktopts*,int) ; 
 int /*<<< orphan*/  free (struct ip6_pktopts*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_initpktopts (struct ip6_pktopts*) ; 
 struct ip6_pktopts* malloc (int,int /*<<< orphan*/ ,int) ; 

struct ip6_pktopts *
ip6_copypktopts(struct ip6_pktopts *src, int canwait)
{
	int error;
	struct ip6_pktopts *dst;

	dst = malloc(sizeof(*dst), M_IP6OPT, canwait);
	if (dst == NULL)
		return (NULL);
	ip6_initpktopts(dst);

	if ((error = copypktopts(dst, src, canwait)) != 0) {
		free(dst, M_IP6OPT);
		return (NULL);
	}

	return (dst);
}