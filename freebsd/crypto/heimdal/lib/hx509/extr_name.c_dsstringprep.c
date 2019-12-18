#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wind_profile_flags ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_7__ {int /*<<< orphan*/  utf8String; } ;
struct TYPE_8__ {int element; TYPE_1__ u; } ;
typedef  TYPE_2__ DirectoryString ;

/* Variables and functions */
 int /*<<< orphan*/  COPYCHARARRAY (TYPE_2__ const*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  COPYVALARRAY (TYPE_2__ const*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  COPYVOIDARRAY (TYPE_2__ const*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int WIND_ERR_OVERRUN ; 
 int /*<<< orphan*/  WIND_PROFILE_LDAP ; 
 int /*<<< orphan*/  WIND_PROFILE_LDAP_CASE ; 
 int /*<<< orphan*/  WIND_PROFILE_LDAP_CASE_EXACT_ATTRIBUTE ; 
 int /*<<< orphan*/  _hx509_abort (char*,int) ; 
 int /*<<< orphan*/  bmpString ; 
#define  choice_DirectoryString_bmpString 133 
#define  choice_DirectoryString_ia5String 132 
#define  choice_DirectoryString_printableString 131 
#define  choice_DirectoryString_teletexString 130 
#define  choice_DirectoryString_universalString 129 
#define  choice_DirectoryString_utf8String 128 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ia5String ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  printableString ; 
 int /*<<< orphan*/  teletexString ; 
 int /*<<< orphan*/  universalString ; 
 int wind_stringprep (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ; 
 int wind_utf8ucs4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 int wind_utf8ucs4_length (int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int
dsstringprep(const DirectoryString *ds, uint32_t **rname, size_t *rlen)
{
    wind_profile_flags flags;
    size_t i, len;
    int ret;
    uint32_t *name;

    *rname = NULL;
    *rlen = 0;

    switch(ds->element) {
    case choice_DirectoryString_ia5String:
	flags = WIND_PROFILE_LDAP;
	COPYVOIDARRAY(ds, ia5String, len, name);
	break;
    case choice_DirectoryString_printableString:
	flags = WIND_PROFILE_LDAP;
	flags |= WIND_PROFILE_LDAP_CASE_EXACT_ATTRIBUTE;
	COPYVOIDARRAY(ds, printableString, len, name);
	break;
    case choice_DirectoryString_teletexString:
	flags = WIND_PROFILE_LDAP_CASE;
	COPYCHARARRAY(ds, teletexString, len, name);
	break;
    case choice_DirectoryString_bmpString:
	flags = WIND_PROFILE_LDAP;
	COPYVALARRAY(ds, bmpString, len, name);
	break;
    case choice_DirectoryString_universalString:
	flags = WIND_PROFILE_LDAP;
	COPYVALARRAY(ds, universalString, len, name);
	break;
    case choice_DirectoryString_utf8String:
	flags = WIND_PROFILE_LDAP;
	ret = wind_utf8ucs4_length(ds->u.utf8String, &len);
	if (ret)
	    return ret;
	name = malloc(len * sizeof(name[0]));
	if (name == NULL)
	    return ENOMEM;
	ret = wind_utf8ucs4(ds->u.utf8String, name, &len);
	if (ret) {
	    free(name);
	    return ret;
	}
	break;
    default:
	_hx509_abort("unknown directory type: %d", ds->element);
    }

    *rlen = len;
    /* try a couple of times to get the length right, XXX gross */
    for (i = 0; i < 4; i++) {
	*rlen = *rlen * 2;
	*rname = malloc(*rlen * sizeof((*rname)[0]));

	ret = wind_stringprep(name, len, *rname, rlen, flags);
	if (ret == WIND_ERR_OVERRUN) {
	    free(*rname);
	    *rname = NULL;
	    continue;
	} else
	    break;
    }
    free(name);
    if (ret) {
	if (*rname)
	    free(*rname);
	*rname = NULL;
	*rlen = 0;
	return ret;
    }

    return 0;
}