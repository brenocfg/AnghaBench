#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ip; } ;
typedef  TYPE_1__ address_t ;

/* Variables and functions */
 int /*<<< orphan*/  WINS_MyAddress () ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Net_MyAddress( address_t *address ){
	strcpy( address->ip, WINS_MyAddress() );
}