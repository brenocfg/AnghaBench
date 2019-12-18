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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_pop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_free_upto(BIO *f, BIO *upto)
{
    if (upto) {
        BIO *tbio;
        do {
            tbio = BIO_pop(f);
            BIO_free(f);
            f = tbio;
        }
        while (f && f != upto);
    } else
        BIO_free_all(f);
}