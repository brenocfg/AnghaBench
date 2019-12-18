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
struct pnpinfo {int /*<<< orphan*/  pi_ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (struct pnpinfo*,int) ; 
 struct pnpinfo* malloc (int) ; 

struct pnpinfo *
pnp_allocinfo(void)
{
    struct pnpinfo	*pi;
    
    pi = malloc(sizeof(struct pnpinfo));
    bzero(pi, sizeof(struct pnpinfo));
    STAILQ_INIT(&pi->pi_ident);
    return(pi);
}