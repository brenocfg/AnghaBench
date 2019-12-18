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
typedef  unsigned int uint32_t ;
typedef  unsigned int uChar ;
struct hashValue {unsigned int a; unsigned int b; unsigned int c; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mix (unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void
addWordToHash(struct hashValue *h, const Char *word)
{
    uint32_t a = h->a, b = h->b, c = h->c;
#ifdef SHORT_STRINGS
#ifdef WIDE_STRINGS
    assert(sizeof(Char) >= 4);
    while (1) {
	unsigned k;
	if ((k = (uChar)*word++) == 0) break; a += k;
	if ((k = (uChar)*word++) == 0) break; b += k;
	if ((k = (uChar)*word++) == 0) break; c += k;
	mix(a, b, c);
    }
#else
    assert(sizeof(Char) == 2);
    while (1) {
	unsigned k;
	if ((k = (uChar)*word++) == 0) break; a += k;
	if ((k = (uChar)*word++) == 0) break; a += k << 16;
	if ((k = (uChar)*word++) == 0) break; b += k;
	if ((k = (uChar)*word++) == 0) break; b += k << 16;
	if ((k = (uChar)*word++) == 0) break; c += k;
	if ((k = (uChar)*word++) == 0) break; c += k << 16;
	mix(a, b, c);
    }
#endif
#else
    assert(sizeof(Char) == 1);
    while (1) {
	unsigned k;
	if ((k = *word++) == 0) break; a += k;
	if ((k = *word++) == 0) break; a += k << 8;
	if ((k = *word++) == 0) break; a += k << 16;
	if ((k = *word++) == 0) break; a += k << 24;
	if ((k = *word++) == 0) break; b += k;
	if ((k = *word++) == 0) break; b += k << 8;
	if ((k = *word++) == 0) break; b += k << 16;
	if ((k = *word++) == 0) break; b += k << 24;
	if ((k = *word++) == 0) break; c += k;
	if ((k = *word++) == 0) break; c += k << 8;
	if ((k = *word++) == 0) break; c += k << 16;
	if ((k = *word++) == 0) break; c += k << 24;
	mix(a, b, c);
    }
#endif
    h->a = a, h->b = b, h->c = c;
}