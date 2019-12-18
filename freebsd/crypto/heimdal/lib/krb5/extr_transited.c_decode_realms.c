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
struct tr_realm {int dummy; } ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 struct tr_realm* append_realm (struct tr_realm*,struct tr_realm*) ; 
 int /*<<< orphan*/  free (struct tr_realm*) ; 
 int /*<<< orphan*/  free_realms (struct tr_realm*) ; 
 int krb5_enomem (int /*<<< orphan*/ ) ; 
 struct tr_realm* make_realm (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static int
decode_realms(krb5_context context,
	      const char *tr, int length, struct tr_realm **realms)
{
    struct tr_realm *r = NULL;

    char *tmp;
    int quote = 0;
    const char *start = tr;
    int i;

    for(i = 0; i < length; i++){
	if(quote){
	    quote = 0;
	    continue;
	}
	if(tr[i] == '\\'){
	    quote = 1;
	    continue;
	}
	if(tr[i] == ','){
	    tmp = malloc(tr + i - start + 1);
	    if(tmp == NULL)
		return krb5_enomem(context);
	    memcpy(tmp, start, tr + i - start);
	    tmp[tr + i - start] = '\0';
	    r = make_realm(tmp);
	    if(r == NULL){
		free_realms(*realms);
		return krb5_enomem(context);
	    }
	    *realms = append_realm(*realms, r);
	    start = tr + i + 1;
	}
    }
    tmp = malloc(tr + i - start + 1);
    if(tmp == NULL){
	free(*realms);
	return krb5_enomem(context);
    }
    memcpy(tmp, start, tr + i - start);
    tmp[tr + i - start] = '\0';
    r = make_realm(tmp);
    if(r == NULL){
	free_realms(*realms);
	return krb5_enomem(context);
    }
    *realms = append_realm(*realms, r);

    return 0;
}