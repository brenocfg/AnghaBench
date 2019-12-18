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
typedef  int u_char ;
struct ess_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ ess_cmd (struct ess_info*,int) ; 
 int ess_get_byte (struct ess_info*) ; 

__attribute__((used)) static int
ess_read(struct ess_info *sc, u_char reg)
{
    	return (ess_cmd(sc, 0xc0) && ess_cmd(sc, reg))? ess_get_byte(sc) : -1;
}