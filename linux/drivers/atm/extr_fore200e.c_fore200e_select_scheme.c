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
struct atm_vcc {int vci; int /*<<< orphan*/  vpi; int /*<<< orphan*/  itf; } ;

/* Variables and functions */
 int BUFFER_SCHEME_ONE ; 
 int BUFFER_SCHEME_TWO ; 
 int /*<<< orphan*/  DPRINTK (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
fore200e_select_scheme(struct atm_vcc* vcc)
{
    /* fairly balance the VCs over (identical) buffer schemes */
    int scheme = vcc->vci % 2 ? BUFFER_SCHEME_ONE : BUFFER_SCHEME_TWO;

    DPRINTK(1, "VC %d.%d.%d uses buffer scheme %d\n",
	    vcc->itf, vcc->vpi, vcc->vci, scheme);

    return scheme;
}