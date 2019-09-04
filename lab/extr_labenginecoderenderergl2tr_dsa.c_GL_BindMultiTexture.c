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
struct TYPE_2__ {size_t* textures; } ;
typedef  size_t GLuint ;
typedef  scalar_t__ GLenum ;

/* Variables and functions */
 scalar_t__ GL_TEXTURE0 ; 
 scalar_t__ GL_TEXTURE_CUBE_MAP ; 
 scalar_t__ GL_TEXTURE_CUBE_MAP_NEGATIVE_Z ; 
 scalar_t__ GL_TEXTURE_CUBE_MAP_POSITIVE_X ; 
 TYPE_1__ glDsaState ; 
 int /*<<< orphan*/  qglBindMultiTextureEXT (scalar_t__,scalar_t__,size_t) ; 

int GL_BindMultiTexture(GLenum texunit, GLenum target, GLuint texture)
{
	GLuint tmu = texunit - GL_TEXTURE0;

	if (glDsaState.textures[tmu] == texture)
		return 0;

	if (target >= GL_TEXTURE_CUBE_MAP_POSITIVE_X && target <= GL_TEXTURE_CUBE_MAP_NEGATIVE_Z)
		target = GL_TEXTURE_CUBE_MAP;

	qglBindMultiTextureEXT(texunit, target, texture);
	glDsaState.textures[tmu] = texture;
	return 1;
}