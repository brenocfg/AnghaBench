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
struct decoded_addr {int dummy; } ;

/* Variables and functions */
 scalar_t__ skx_mad_decode (struct decoded_addr*) ; 
 scalar_t__ skx_rir_decode (struct decoded_addr*) ; 
 scalar_t__ skx_sad_decode (struct decoded_addr*) ; 
 scalar_t__ skx_tad_decode (struct decoded_addr*) ; 

__attribute__((used)) static bool skx_decode(struct decoded_addr *res)
{
	return skx_sad_decode(res) && skx_tad_decode(res) &&
		skx_rir_decode(res) && skx_mad_decode(res);
}