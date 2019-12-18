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
struct kevent {int flags; scalar_t__ ident; scalar_t__ filter; scalar_t__ fflags; scalar_t__ data; scalar_t__ udata; scalar_t__* ext; } ;

/* Variables and functions */
 int EV_ADD ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  free (char*) ; 
 char* kevent_to_str (struct kevent*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 

void
kevent_cmp(struct kevent *k1, struct kevent *k2)
{
    char *kev1_str;
    char *kev2_str;
    
/* XXX-
   Workaround for inconsistent implementation of kevent(2) 
 */
#ifdef __FreeBSD__
    if (k1->flags & EV_ADD)
        k2->flags |= EV_ADD;
#endif
    if (k1->ident != k2->ident || k1->filter != k2->filter ||
      k1->flags != k2->flags || k1->fflags != k2->fflags ||
      k1->data != k2->data || k1->udata != k2->udata ||
      k1->ext[0] != k2->ext[0] || k1->ext[1] != k2->ext[1] ||
      k1->ext[0] != k2->ext[2] || k1->ext[0] != k2->ext[3]) {
        kev1_str = kevent_to_str(k1);
        kev2_str = kevent_to_str(k2);
        printf("kevent_cmp: mismatch:\n  %s !=\n  %s\n", 
               kev1_str, kev2_str);
        free(kev1_str);
        free(kev2_str);
        abort();
    }
}