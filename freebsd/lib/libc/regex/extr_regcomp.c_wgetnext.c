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
typedef  int /*<<< orphan*/  wint_t ;
typedef  int /*<<< orphan*/  wchar_t ;
struct parse {scalar_t__ next; scalar_t__ end; } ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  mbs ;

/* Variables and functions */
 int /*<<< orphan*/  REG_ILLSEQ ; 
 int /*<<< orphan*/  SETERROR (int /*<<< orphan*/ ) ; 
 size_t mbrtowc (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static wint_t
wgetnext(struct parse *p)
{
	mbstate_t mbs;
	wchar_t wc;
	size_t n;

	memset(&mbs, 0, sizeof(mbs));
	n = mbrtowc(&wc, p->next, p->end - p->next, &mbs);
	if (n == (size_t)-1 || n == (size_t)-2) {
		SETERROR(REG_ILLSEQ);
		return (0);
	}
	if (n == 0)
		n = 1;
	p->next += n;
	return (wc);
}