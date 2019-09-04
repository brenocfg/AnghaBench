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
typedef  int /*<<< orphan*/  byte ;
struct TYPE_2__ {int /*<<< orphan*/ * (* Hunk_AllocateTempMemory ) (scalar_t__) ;} ;
typedef  scalar_t__ GLint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_PACK_ALIGNMENT ; 
 int /*<<< orphan*/  GL_RGB ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int PAD (int,scalar_t__) ; 
 int /*<<< orphan*/ * PADP (intptr_t,scalar_t__) ; 
 int /*<<< orphan*/  qglGetIntegerv (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  qglReadPixels (int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ ri ; 
 int /*<<< orphan*/ * stub1 (scalar_t__) ; 

byte *RB_ReadPixels(int x, int y, int width, int height, size_t *offset, int *padlen)
{
	byte *buffer, *bufstart;
	int padwidth, linelen;
	GLint packAlign;
	
	qglGetIntegerv(GL_PACK_ALIGNMENT, &packAlign);
	
	linelen = width * 3;
	padwidth = PAD(linelen, packAlign);
	
	// Allocate a few more bytes so that we can choose an alignment we like
	buffer = ri.Hunk_AllocateTempMemory(padwidth * height + *offset + packAlign - 1);
	
	bufstart = PADP((intptr_t) buffer + *offset, packAlign);

	qglReadPixels(x, y, width, height, GL_RGB, GL_UNSIGNED_BYTE, bufstart);
	
	*offset = bufstart - buffer;
	*padlen = padwidth - linelen;
	
	return buffer;
}