#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* ptr; unsigned long size; } ;
struct diff_words_buffer {TYPE_1__ text; int /*<<< orphan*/  alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (char*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned long) ; 

__attribute__((used)) static void diff_words_append(char *line, unsigned long len,
		struct diff_words_buffer *buffer)
{
	ALLOC_GROW(buffer->text.ptr, buffer->text.size + len, buffer->alloc);
	line++;
	len--;
	memcpy(buffer->text.ptr + buffer->text.size, line, len);
	buffer->text.size += len;
	buffer->text.ptr[buffer->text.size] = '\0';
}