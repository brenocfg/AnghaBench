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
struct streebog_uint512 {int dummy; } ;

/* Variables and functions */
 struct streebog_uint512* C ; 
 int /*<<< orphan*/  streebog_xlps (struct streebog_uint512*,struct streebog_uint512*,struct streebog_uint512*) ; 

__attribute__((used)) static void streebog_round(int i, struct streebog_uint512 *Ki,
			   struct streebog_uint512 *data)
{
	streebog_xlps(Ki, &C[i], Ki);
	streebog_xlps(Ki, data, data);
}