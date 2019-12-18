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
struct roff_node {int flags; scalar_t__ tok; TYPE_1__* prev; } ;
struct html {int dummy; } ;
struct TYPE_2__ {scalar_t__ tok; } ;

/* Variables and functions */
#define  MDOC_Fd 133 
#define  MDOC_Fn 132 
#define  MDOC_Fo 131 
#define  MDOC_Ft 130 
#define  MDOC_In 129 
#define  MDOC_Vt 128 
 int NODE_SYNPRETTY ; 
 int /*<<< orphan*/  TAG_BR ; 
 int /*<<< orphan*/  TAG_P ; 
 int /*<<< orphan*/  html_close_paragraph (struct html*) ; 
 int /*<<< orphan*/  print_otag (struct html*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
synopsis_pre(struct html *h, const struct roff_node *n)
{

	if (NULL == n->prev || ! (NODE_SYNPRETTY & n->flags))
		return;

	if (n->prev->tok == n->tok &&
	    MDOC_Fo != n->tok &&
	    MDOC_Ft != n->tok &&
	    MDOC_Fn != n->tok) {
		print_otag(h, TAG_BR, "");
		return;
	}

	switch (n->prev->tok) {
	case MDOC_Fd:
	case MDOC_Fn:
	case MDOC_Fo:
	case MDOC_In:
	case MDOC_Vt:
		break;
	case MDOC_Ft:
		if (n->tok != MDOC_Fn && n->tok != MDOC_Fo)
			break;
		/* FALLTHROUGH */
	default:
		print_otag(h, TAG_BR, "");
		return;
	}
	html_close_paragraph(h);
	print_otag(h, TAG_P, "c", "Pp");
}