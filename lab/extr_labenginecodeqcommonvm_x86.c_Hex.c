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

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int /*<<< orphan*/  VMFREE_BUFFERS () ; 

__attribute__((used)) static int Hex( int c ) {
	if ( c >= 'a' && c <= 'f' ) {
		return 10 + c - 'a';
	}
	if ( c >= 'A' && c <= 'F' ) {
		return 10 + c - 'A';
	}
	if ( c >= '0' && c <= '9' ) {
		return c - '0';
	}

	VMFREE_BUFFERS();
	Com_Error( ERR_DROP, "Hex: bad char '%c'", c );

	return 0;
}