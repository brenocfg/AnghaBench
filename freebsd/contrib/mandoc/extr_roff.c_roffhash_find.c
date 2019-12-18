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
struct roffreq {int tok; } ;
struct ohash {int dummy; } ;
typedef  enum roff_tok { ____Placeholder_roff_tok } roff_tok ;

/* Variables and functions */
 int TOKEN_NONE ; 
 struct roffreq* ohash_find (struct ohash*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ohash_qlookup (struct ohash*,char const*) ; 
 int /*<<< orphan*/  ohash_qlookupi (struct ohash*,char const*,char const**) ; 

enum roff_tok
roffhash_find(struct ohash *htab, const char *name, size_t sz)
{
	struct roffreq	*req;
	const char	*end;

	if (sz) {
		end = name + sz;
		req = ohash_find(htab, ohash_qlookupi(htab, name, &end));
	} else
		req = ohash_find(htab, ohash_qlookup(htab, name));
	return req == NULL ? TOKEN_NONE : req->tok;
}