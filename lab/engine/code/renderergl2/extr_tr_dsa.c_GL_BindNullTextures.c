#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ texunit; scalar_t__* textures; } ;
struct TYPE_3__ {scalar_t__ directStateAccess; } ;

/* Variables and functions */
 scalar_t__ GL_TEXTURE0 ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int NUM_TEXTURE_BUNDLES ; 
 TYPE_2__ glDsaState ; 
 TYPE_1__ glRefConfig ; 
 int /*<<< orphan*/  qglActiveTexture (scalar_t__) ; 
 int /*<<< orphan*/  qglBindMultiTextureEXT (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void GL_BindNullTextures(void)
{
	int i;

	if (glRefConfig.directStateAccess)
	{
		for (i = 0; i < NUM_TEXTURE_BUNDLES; i++)
		{
			qglBindMultiTextureEXT(GL_TEXTURE0 + i, GL_TEXTURE_2D, 0);
			glDsaState.textures[i] = 0;
		}
	}
	else
	{
		for (i = 0; i < NUM_TEXTURE_BUNDLES; i++)
		{
			qglActiveTexture(GL_TEXTURE0 + i);
			qglBindTexture(GL_TEXTURE_2D, 0);
			glDsaState.textures[i] = 0;
		}

		qglActiveTexture(GL_TEXTURE0);
		glDsaState.texunit = GL_TEXTURE0;
	}
}