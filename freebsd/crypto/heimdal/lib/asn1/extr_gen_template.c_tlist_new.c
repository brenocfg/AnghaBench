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
struct tlist {int /*<<< orphan*/  template; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_TAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct tlist* calloc (int,int) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

__attribute__((used)) static struct tlist *
tlist_new(const char *name)
{
    struct tlist *tl = calloc(1, sizeof(*tl));
    tl->name = strdup(name);
    ASN1_TAILQ_INIT(&tl->template);
    return tl;
}