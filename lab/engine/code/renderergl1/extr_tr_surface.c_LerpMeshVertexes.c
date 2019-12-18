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
typedef  int /*<<< orphan*/  md3Surface_t ;
struct TYPE_2__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  LerpMeshVertexes_altivec (int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  LerpMeshVertexes_scalar (int /*<<< orphan*/ *,float) ; 
 TYPE_1__* com_altivec ; 

__attribute__((used)) static void LerpMeshVertexes(md3Surface_t *surf, float backlerp)
{
#if idppc_altivec
	if (com_altivec->integer) {
		// must be in a separate translation unit or G3 systems will crash.
		LerpMeshVertexes_altivec( surf, backlerp );
		return;
	}
#endif // idppc_altivec
	LerpMeshVertexes_scalar( surf, backlerp );
}