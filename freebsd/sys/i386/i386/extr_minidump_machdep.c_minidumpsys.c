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
struct dumperinfo {int dummy; } ;

/* Variables and functions */
 int minidumpsys_nopae (struct dumperinfo*) ; 
 int minidumpsys_pae (struct dumperinfo*) ; 
 scalar_t__ pae_mode ; 

int
minidumpsys(struct dumperinfo *di)
{

	return (pae_mode ? minidumpsys_pae(di) : minidumpsys_nopae(di));
}