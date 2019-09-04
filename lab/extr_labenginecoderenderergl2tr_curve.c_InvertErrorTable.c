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
typedef  int /*<<< orphan*/  copy ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memcpy (float**,float**,int) ; 
 int MAX_GRID_SIZE ; 

__attribute__((used)) static void InvertErrorTable( float errorTable[2][MAX_GRID_SIZE], int width, int height ) {
	int		i;
	float	copy[2][MAX_GRID_SIZE];

	Com_Memcpy( copy, errorTable, sizeof( copy ) );

	for ( i = 0 ; i < width ; i++ ) {
		errorTable[1][i] = copy[0][i];	//[width-1-i];
	}

	for ( i = 0 ; i < height ; i++ ) {
		errorTable[0][i] = copy[1][height-1-i];
	}

}