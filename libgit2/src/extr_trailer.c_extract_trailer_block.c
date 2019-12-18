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
 size_t find_patch_start (char const*) ; 
 size_t find_trailer_end (char const*,size_t) ; 
 size_t find_trailer_start (char const*,size_t) ; 
 char* git__malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

__attribute__((used)) static char *extract_trailer_block(const char *message, size_t* len)
{
	size_t patch_start = find_patch_start(message);
	size_t trailer_end = find_trailer_end(message, patch_start);
	size_t trailer_start = find_trailer_start(message, trailer_end);

	size_t trailer_len = trailer_end - trailer_start;

	char *buffer = git__malloc(trailer_len + 1);
	if (buffer == NULL)
		return NULL;

	memcpy(buffer, message + trailer_start, trailer_len);
	buffer[trailer_len] = 0;

	*len = trailer_len;

	return buffer;
}