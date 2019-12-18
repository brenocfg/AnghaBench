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
struct tr_realm {char const* realm; int /*<<< orphan*/  leading_space; scalar_t__ leading_slash; scalar_t__ trailing_dot; struct tr_realm* next; } ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  free (char const*) ; 
 int /*<<< orphan*/  free_realms (struct tr_realm*) ; 
 int krb5_enomem (int /*<<< orphan*/ ) ; 
 char* malloc (size_t) ; 
 char* realloc (char const*,size_t) ; 
 int /*<<< orphan*/  strlcat (char*,char const*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
expand_realms(krb5_context context,
	      struct tr_realm *realms, const char *client_realm)
{
    struct tr_realm *r;
    const char *prev_realm = NULL;
    for(r = realms; r; r = r->next){
	if(r->trailing_dot){
	    char *tmp;
	    size_t len;

	    if(prev_realm == NULL)
		prev_realm = client_realm;

	    len = strlen(r->realm) + strlen(prev_realm) + 1;

	    tmp = realloc(r->realm, len);
	    if(tmp == NULL){
		free_realms(realms);
		return krb5_enomem(context);
	    }
	    r->realm = tmp;
	    strlcat(r->realm, prev_realm, len);
	}else if(r->leading_slash && !r->leading_space && prev_realm){
	    /* yet another exception: if you use x500-names, the
               leading realm doesn't have to be "quoted" with a space */
	    char *tmp;
	    size_t len = strlen(r->realm) + strlen(prev_realm) + 1;

	    tmp = malloc(len);
	    if(tmp == NULL){
		free_realms(realms);
		return krb5_enomem(context);
	    }
	    strlcpy(tmp, prev_realm, len);
	    strlcat(tmp, r->realm, len);
	    free(r->realm);
	    r->realm = tmp;
	}
	prev_realm = r->realm;
    }
    return 0;
}