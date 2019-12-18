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

void TCMod( tcMod_t mod, float st[ 2 ] ){
	float old[ 2 ];


	old[ 0 ] = st[ 0 ];
	old[ 1 ] = st[ 1 ];
	st[ 0 ] = ( mod[ 0 ][ 0 ] * old[ 0 ] ) + ( mod[ 0 ][ 1 ] * old[ 1 ] ) + mod[ 0 ][ 2 ];
	st[ 1 ] = ( mod[ 1 ][ 0 ] * old[ 0 ] ) + ( mod[ 1 ][ 1 ] * old[ 1 ] ) + mod[ 1 ][ 2 ];
}