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
struct html {int dummy; } ;
struct eqn_box {scalar_t__ type; int expectargs; int pos; char* top; char* bottom; char* text; int font; char* left; char* right; struct eqn_box* next; struct eqn_box* first; TYPE_1__* parent; } ;
typedef  enum htmltag { ____Placeholder_htmltag } htmltag ;
typedef  enum eqn_fontt { ____Placeholder_eqn_fontt } eqn_fontt ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
#define  EQNFONT_BOLD 140 
#define  EQNFONT_FAT 139 
#define  EQNFONT_ITALIC 138 
#define  EQNFONT_NONE 137 
#define  EQNFONT_ROMAN 136 
#define  EQNPOS_FROM 135 
#define  EQNPOS_FROMTO 134 
#define  EQNPOS_OVER 133 
#define  EQNPOS_SQRT 132 
#define  EQNPOS_SUB 131 
#define  EQNPOS_SUBSUP 130 
#define  EQNPOS_SUP 129 
#define  EQNPOS_TO 128 
 scalar_t__ EQN_LIST ; 
 scalar_t__ EQN_MATRIX ; 
 scalar_t__ EQN_PILE ; 
 int /*<<< orphan*/  TAG_MFENCED ; 
 int TAG_MFRAC ; 
 int TAG_MI ; 
 int TAG_MN ; 
 int TAG_MO ; 
 int TAG_MOVER ; 
 int TAG_MROW ; 
 int TAG_MSQRT ; 
 int TAG_MSUB ; 
 int TAG_MSUBSUP ; 
 int TAG_MSUP ; 
 int TAG_MTABLE ; 
 int TAG_MTD ; 
 int TAG_MTR ; 
 int TAG_MUNDER ; 
 int TAG_MUNDEROVER ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ isalnum (unsigned char) ; 
 scalar_t__ isalpha (unsigned char) ; 
 scalar_t__ isdigit (unsigned char) ; 
 int /*<<< orphan*/  mandoc_escape (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct tag* print_otag (struct html*,int,char*,...) ; 
 int /*<<< orphan*/  print_tagq (struct html*,struct tag*) ; 
 int /*<<< orphan*/  print_text (struct html*,char*) ; 

__attribute__((used)) static void
eqn_box(struct html *p, const struct eqn_box *bp)
{
	struct tag	*post, *row, *cell, *t;
	const struct eqn_box *child, *parent;
	const char	*cp;
	size_t		 i, j, rows;
	enum htmltag	 tag;
	enum eqn_fontt	 font;

	if (NULL == bp)
		return;

	post = NULL;

	/*
	 * Special handling for a matrix, which is presented to us in
	 * column order, but must be printed in row-order.
	 */
	if (EQN_MATRIX == bp->type) {
		if (NULL == bp->first)
			goto out;
		if (bp->first->type != EQN_LIST ||
		    bp->first->expectargs == 1) {
			eqn_box(p, bp->first);
			goto out;
		}
		if (NULL == (parent = bp->first->first))
			goto out;
		/* Estimate the number of rows, first. */
		if (NULL == (child = parent->first))
			goto out;
		for (rows = 0; NULL != child; rows++)
			child = child->next;
		/* Print row-by-row. */
		post = print_otag(p, TAG_MTABLE, "");
		for (i = 0; i < rows; i++) {
			parent = bp->first->first;
			row = print_otag(p, TAG_MTR, "");
			while (NULL != parent) {
				child = parent->first;
				for (j = 0; j < i; j++) {
					if (NULL == child)
						break;
					child = child->next;
				}
				cell = print_otag(p, TAG_MTD, "");
				/*
				 * If we have no data for this
				 * particular cell, then print a
				 * placeholder and continue--don't puke.
				 */
				if (NULL != child)
					eqn_box(p, child->first);
				print_tagq(p, cell);
				parent = parent->next;
			}
			print_tagq(p, row);
		}
		goto out;
	}

	switch (bp->pos) {
	case EQNPOS_TO:
		post = print_otag(p, TAG_MOVER, "");
		break;
	case EQNPOS_SUP:
		post = print_otag(p, TAG_MSUP, "");
		break;
	case EQNPOS_FROM:
		post = print_otag(p, TAG_MUNDER, "");
		break;
	case EQNPOS_SUB:
		post = print_otag(p, TAG_MSUB, "");
		break;
	case EQNPOS_OVER:
		post = print_otag(p, TAG_MFRAC, "");
		break;
	case EQNPOS_FROMTO:
		post = print_otag(p, TAG_MUNDEROVER, "");
		break;
	case EQNPOS_SUBSUP:
		post = print_otag(p, TAG_MSUBSUP, "");
		break;
	case EQNPOS_SQRT:
		post = print_otag(p, TAG_MSQRT, "");
		break;
	default:
		break;
	}

	if (bp->top || bp->bottom) {
		assert(NULL == post);
		if (bp->top && NULL == bp->bottom)
			post = print_otag(p, TAG_MOVER, "");
		else if (bp->top && bp->bottom)
			post = print_otag(p, TAG_MUNDEROVER, "");
		else if (bp->bottom)
			post = print_otag(p, TAG_MUNDER, "");
	}

	if (EQN_PILE == bp->type) {
		assert(NULL == post);
		if (bp->first != NULL &&
		    bp->first->type == EQN_LIST &&
		    bp->first->expectargs > 1)
			post = print_otag(p, TAG_MTABLE, "");
	} else if (bp->type == EQN_LIST && bp->expectargs > 1 &&
	    bp->parent && bp->parent->type == EQN_PILE) {
		assert(NULL == post);
		post = print_otag(p, TAG_MTR, "");
		print_otag(p, TAG_MTD, "");
	}

	if (bp->text != NULL) {
		assert(post == NULL);
		tag = TAG_MI;
		cp = bp->text;
		if (isdigit((unsigned char)cp[0]) ||
		    (cp[0] == '.' && isdigit((unsigned char)cp[1]))) {
			tag = TAG_MN;
			while (*++cp != '\0') {
				if (*cp != '.' &&
				    isdigit((unsigned char)*cp) == 0) {
					tag = TAG_MI;
					break;
				}
			}
		} else if (*cp != '\0' && isalpha((unsigned char)*cp) == 0) {
			tag = TAG_MO;
			while (*cp != '\0') {
				if (cp[0] == '\\' && cp[1] != '\0') {
					cp++;
					mandoc_escape(&cp, NULL, NULL);
				} else if (isalnum((unsigned char)*cp)) {
					tag = TAG_MI;
					break;
				} else
					cp++;
			}
		}
		font = bp->font;
		if (bp->text[0] != '\0' &&
		    (((tag == TAG_MN || tag == TAG_MO) &&
		      font == EQNFONT_ROMAN) ||
		     (tag == TAG_MI && font == (bp->text[1] == '\0' ?
		      EQNFONT_ITALIC : EQNFONT_ROMAN))))
			font = EQNFONT_NONE;
		switch (font) {
		case EQNFONT_NONE:
			post = print_otag(p, tag, "");
			break;
		case EQNFONT_ROMAN:
			post = print_otag(p, tag, "?", "fontstyle", "normal");
			break;
		case EQNFONT_BOLD:
		case EQNFONT_FAT:
			post = print_otag(p, tag, "?", "fontweight", "bold");
			break;
		case EQNFONT_ITALIC:
			post = print_otag(p, tag, "?", "fontstyle", "italic");
			break;
		default:
			abort();
		}
		print_text(p, bp->text);
	} else if (NULL == post) {
		if (NULL != bp->left || NULL != bp->right)
			post = print_otag(p, TAG_MFENCED, "??",
			    "open", bp->left == NULL ? "" : bp->left,
			    "close", bp->right == NULL ? "" : bp->right);
		if (NULL == post)
			post = print_otag(p, TAG_MROW, "");
		else
			print_otag(p, TAG_MROW, "");
	}

	eqn_box(p, bp->first);

out:
	if (NULL != bp->bottom) {
		t = print_otag(p, TAG_MO, "");
		print_text(p, bp->bottom);
		print_tagq(p, t);
	}
	if (NULL != bp->top) {
		t = print_otag(p, TAG_MO, "");
		print_text(p, bp->top);
		print_tagq(p, t);
	}

	if (NULL != post)
		print_tagq(p, post);

	eqn_box(p, bp->next);
}