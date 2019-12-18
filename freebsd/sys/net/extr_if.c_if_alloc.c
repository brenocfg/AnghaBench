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
typedef  int /*<<< orphan*/  u_char ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IF_NODOM ; 
 struct ifnet* if_alloc_domain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct ifnet *
if_alloc(u_char type)
{

	return (if_alloc_domain(type, IF_NODOM));
}