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
struct TYPE_3__ {struct TYPE_3__* tag_name; struct TYPE_3__* message; int /*<<< orphan*/  tagger; } ;
typedef  TYPE_1__ git_tag ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ ) ; 

void git_tag__free(void *_tag)
{
	git_tag *tag = _tag;
	git_signature_free(tag->tagger);
	git__free(tag->message);
	git__free(tag->tag_name);
	git__free(tag);
}