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
struct tag {int dummy; } ;
struct roff_node {scalar_t__ type; } ;
struct roff_meta {TYPE_1__* first; } ;
struct html {int oflags; } ;
struct TYPE_2__ {struct roff_node* child; } ;

/* Variables and functions */
 int HTML_FRAGMENT ; 
 scalar_t__ ROFFT_COMMENT ; 
 int /*<<< orphan*/  TAG_BODY ; 
 int /*<<< orphan*/  TAG_DIV ; 
 int /*<<< orphan*/  TAG_HEAD ; 
 int /*<<< orphan*/  TAG_HTML ; 
 int /*<<< orphan*/  mdoc_root_post (struct roff_meta const*,struct html*) ; 
 int /*<<< orphan*/  mdoc_root_pre (struct roff_meta const*,struct html*) ; 
 int /*<<< orphan*/  print_gen_comment (struct html*,struct roff_node*) ; 
 int /*<<< orphan*/  print_gen_decls (struct html*) ; 
 int /*<<< orphan*/  print_mdoc_head (struct roff_meta const*,struct html*) ; 
 int /*<<< orphan*/  print_mdoc_nodelist (struct roff_meta const*,struct roff_node*,struct html*) ; 
 struct tag* print_otag (struct html*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  print_tagq (struct html*,struct tag*) ; 

void
html_mdoc(void *arg, const struct roff_meta *mdoc)
{
	struct html		*h;
	struct roff_node	*n;
	struct tag		*t;

	h = (struct html *)arg;
	n = mdoc->first->child;

	if ((h->oflags & HTML_FRAGMENT) == 0) {
		print_gen_decls(h);
		print_otag(h, TAG_HTML, "");
		if (n != NULL && n->type == ROFFT_COMMENT)
			print_gen_comment(h, n);
		t = print_otag(h, TAG_HEAD, "");
		print_mdoc_head(mdoc, h);
		print_tagq(h, t);
		print_otag(h, TAG_BODY, "");
	}

	mdoc_root_pre(mdoc, h);
	t = print_otag(h, TAG_DIV, "c", "manual-text");
	print_mdoc_nodelist(mdoc, n, h);
	print_tagq(h, t);
	mdoc_root_post(mdoc, h);
	print_tagq(h, NULL);
}