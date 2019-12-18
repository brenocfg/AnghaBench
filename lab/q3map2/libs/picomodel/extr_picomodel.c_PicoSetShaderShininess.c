#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {float shininess; } ;
typedef  TYPE_1__ picoShader_t ;

/* Variables and functions */

void PicoSetShaderShininess( picoShader_t *shader, float value ){
	if ( shader == NULL ) {
		return;
	}
	shader->shininess = value;

	/* cap to 0..127 range */
	if ( shader->shininess < 0.0 ) {
		shader->shininess = 0.0;
	}
	if ( shader->shininess > 127.0 ) {
		shader->shininess = 127.0;
	}
}