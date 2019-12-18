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
typedef  int GLenum ;

/* Variables and functions */
#define  GL_DEPTH_COMPONENT 131 
#define  GL_DEPTH_COMPONENT16_ARB 130 
#define  GL_DEPTH_COMPONENT24_ARB 129 
#define  GL_DEPTH_COMPONENT32_ARB 128 
 int GL_RGBA ; 

__attribute__((used)) static GLenum PixelDataFormatFromInternalFormat(GLenum internalFormat)
{
	switch (internalFormat)
	{
		case GL_DEPTH_COMPONENT:
		case GL_DEPTH_COMPONENT16_ARB:
		case GL_DEPTH_COMPONENT24_ARB:
		case GL_DEPTH_COMPONENT32_ARB:
			return GL_DEPTH_COMPONENT;
		default:
			return GL_RGBA;
			break;
	}
}