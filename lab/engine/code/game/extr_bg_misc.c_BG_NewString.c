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
 int BG_BUFFERSIZE ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Com_Memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int bg_buffer_idx ; 
 char* bg_string_buffer ; 
 int strlen (char const*) ; 

char* BG_NewString( const char* str ) {
	char *ptr;
	int len = strlen(str) + 1;
	if ( bg_buffer_idx + len > BG_BUFFERSIZE ) {
		Com_Error( ERR_DROP, "Failed to Allocate new string!" );
	}
	ptr = &bg_string_buffer[bg_buffer_idx];
	Com_Memcpy( ptr, str, len );

	bg_buffer_idx += len;
	return ptr;
}