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
typedef  int /*<<< orphan*/  escape_t ;
typedef  int /*<<< orphan*/  _HZEncodingInfo ;

/* Variables and functions */
 int /*<<< orphan*/  E0SET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  E1SET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TAILQ_FIRST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
_citrus_HZ_encoding_module_uninit(_HZEncodingInfo *ei)
{
	escape_t *escape;

	while ((escape = TAILQ_FIRST(E0SET(ei))) != NULL) {
		TAILQ_REMOVE(E0SET(ei), escape, entry);
		free(GL(escape));
		free(GR(escape));
		free(escape);
	}
	while ((escape = TAILQ_FIRST(E1SET(ei))) != NULL) {
		TAILQ_REMOVE(E1SET(ei), escape, entry);
		free(GL(escape));
		free(GR(escape));
		free(escape);
	}
}