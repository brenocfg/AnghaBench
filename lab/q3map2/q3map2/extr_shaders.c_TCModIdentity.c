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
typedef  float** tcMod_t ;

/* Variables and functions */

void TCModIdentity( tcMod_t mod ){
	mod[ 0 ][ 0 ] = 1.0f;   mod[ 0 ][ 1 ] = 0.0f;   mod[ 0 ][ 2 ] = 0.0f;
	mod[ 1 ][ 0 ] = 0.0f;   mod[ 1 ][ 1 ] = 1.0f;   mod[ 1 ][ 2 ] = 0.0f;
	mod[ 2 ][ 0 ] = 0.0f;   mod[ 2 ][ 1 ] = 0.0f;   mod[ 2 ][ 2 ] = 1.0f;   /* this row is only used for multiples, not transformation */
}