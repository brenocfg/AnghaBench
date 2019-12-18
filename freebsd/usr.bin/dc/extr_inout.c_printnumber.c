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
typedef  int /*<<< orphan*/  u_long ;
typedef  int u_int ;
struct stack {int dummy; } ;
typedef  struct number {scalar_t__ scale; int /*<<< orphan*/ * number; } const number ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BN_ULONG ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 scalar_t__ BN_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_div_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_get_word (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_negative (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mul_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_one (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bmachine_scale () ; 
 int /*<<< orphan*/  bmul_number (struct number const*,struct number const*,struct number const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_checkp (int /*<<< orphan*/ *) ; 
 scalar_t__ charcount ; 
 int /*<<< orphan*/  flushwrap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_number (struct number const*) ; 
 char* get_digit (int /*<<< orphan*/ ,int,int) ; 
 int lastchar ; 
 struct number const* new_number () ; 
 int /*<<< orphan*/  normalize (struct number const*,scalar_t__) ; 
 int /*<<< orphan*/  printwrap (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  putcharwrap (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  scale_number (int /*<<< orphan*/ *,scalar_t__) ; 
 int snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  split_number (struct number const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_clear (struct stack*) ; 
 int /*<<< orphan*/  stack_init (struct stack*) ; 
 char* stack_popstring (struct stack*) ; 
 int /*<<< orphan*/  stack_pushstring (struct stack*,char*) ; 

void
printnumber(FILE *f, const struct number *b, u_int base)
{
	struct number *fract_part, *int_part;
	struct stack stack;
	char *p;
	char buf[11];
	size_t sz;
	unsigned int i;
	int digits;

	charcount = 0;
	lastchar = -1;
	if (BN_is_zero(b->number))
		putcharwrap(f, '0');

	int_part = new_number();
	fract_part = new_number();
	fract_part->scale = b->scale;

	if (base <= 16)
		digits = 1;
	else {
		digits = snprintf(buf, sizeof(buf), "%u", base-1);
	}
	split_number(b, int_part->number, fract_part->number);

	i = 0;
	stack_init(&stack);
	while (!BN_is_zero(int_part->number)) {
		BN_ULONG rem = BN_div_word(int_part->number, base);
		stack_pushstring(&stack, get_digit(rem, digits, base));
		i++;
	}
	sz = i;
	if (BN_is_negative(b->number))
		putcharwrap(f, '-');
	for (i = 0; i < sz; i++) {
		p = stack_popstring(&stack);
		if (base > 16)
			putcharwrap(f, ' ');
		printwrap(f, p);
		free(p);
	}
	stack_clear(&stack);
	if (b->scale > 0) {
		struct number *num_base;
		BIGNUM *mult, *stop;

		putcharwrap(f, '.');
		num_base = new_number();
		bn_check(BN_set_word(num_base->number, base));
		mult = BN_new();
		bn_checkp(mult);
		bn_check(BN_one(mult));
		stop = BN_new();
		bn_checkp(stop);
		bn_check(BN_one(stop));
		scale_number(stop, b->scale);

		i = 0;
		while (BN_cmp(mult, stop) < 0) {
			u_long rem;

			if (i && base > 16)
				putcharwrap(f, ' ');
			i = 1;

			bmul_number(fract_part, fract_part, num_base,
			    bmachine_scale());
			split_number(fract_part, int_part->number, NULL);
			rem = BN_get_word(int_part->number);
			p = get_digit(rem, digits, base);
			int_part->scale = 0;
			normalize(int_part, fract_part->scale);
			bn_check(BN_sub(fract_part->number, fract_part->number,
			    int_part->number));
			printwrap(f, p);
			free(p);
			bn_check(BN_mul_word(mult, base));
		}
		free_number(num_base);
		BN_free(mult);
		BN_free(stop);
	}
	flushwrap(f);
	free_number(int_part);
	free_number(fract_part);
}