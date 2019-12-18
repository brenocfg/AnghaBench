#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_22__ {size_t len; TYPE_7__* val; } ;
struct TYPE_23__ {TYPE_8__ rdnSequence; } ;
struct TYPE_21__ {size_t len; TYPE_1__* val; } ;
struct TYPE_19__ {size_t length; int /*<<< orphan*/ * data; } ;
struct TYPE_18__ {size_t length; int /*<<< orphan*/ * data; } ;
struct TYPE_17__ {char* data; size_t length; } ;
struct TYPE_16__ {char* data; size_t length; } ;
struct TYPE_20__ {char* utf8String; char* teletexString; TYPE_5__ universalString; TYPE_4__ bmpString; TYPE_3__ printableString; TYPE_2__ ia5String; } ;
struct TYPE_14__ {int element; TYPE_6__ u; } ;
struct TYPE_15__ {int /*<<< orphan*/  type; TYPE_11__ value; } ;
struct TYPE_13__ {TYPE_9__ u; } ;
typedef  TYPE_10__ Name ;
typedef  TYPE_11__ DirectoryString ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  _hx509_abort (char*,...) ; 
 int /*<<< orphan*/  append_string (char**,size_t*,char*,int,int) ; 
#define  choice_DirectoryString_bmpString 133 
#define  choice_DirectoryString_ia5String 132 
#define  choice_DirectoryString_printableString 131 
#define  choice_DirectoryString_teletexString 130 
#define  choice_DirectoryString_universalString 129 
#define  choice_DirectoryString_utf8String 128 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 char* oidtostring (int /*<<< orphan*/ *) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 int wind_ucs2utf8 (int /*<<< orphan*/  const*,size_t,char*,int /*<<< orphan*/ *) ; 
 int wind_ucs2utf8_length (int /*<<< orphan*/  const*,size_t,size_t*) ; 
 int wind_ucs4utf8 (int /*<<< orphan*/  const*,size_t,char*,int /*<<< orphan*/ *) ; 
 int wind_ucs4utf8_length (int /*<<< orphan*/  const*,size_t,size_t*) ; 

int
_hx509_Name_to_string(const Name *n, char **str)
{
    size_t total_len = 0;
    size_t i, j, m;
    int ret;

    *str = strdup("");
    if (*str == NULL)
	return ENOMEM;

    for (m = n->u.rdnSequence.len; m > 0; m--) {
	size_t len;
	i = m - 1;

	for (j = 0; j < n->u.rdnSequence.val[i].len; j++) {
	    DirectoryString *ds = &n->u.rdnSequence.val[i].val[j].value;
	    char *oidname;
	    char *ss;

	    oidname = oidtostring(&n->u.rdnSequence.val[i].val[j].type);

	    switch(ds->element) {
	    case choice_DirectoryString_ia5String:
		ss = ds->u.ia5String.data;
		len = ds->u.ia5String.length;
		break;
	    case choice_DirectoryString_printableString:
		ss = ds->u.printableString.data;
		len = ds->u.printableString.length;
		break;
	    case choice_DirectoryString_utf8String:
		ss = ds->u.utf8String;
		len = strlen(ss);
		break;
	    case choice_DirectoryString_bmpString: {
	        const uint16_t *bmp = ds->u.bmpString.data;
		size_t bmplen = ds->u.bmpString.length;
		size_t k;

		ret = wind_ucs2utf8_length(bmp, bmplen, &k);
		if (ret)
		    return ret;

		ss = malloc(k + 1);
		if (ss == NULL)
		    _hx509_abort("allocation failure"); /* XXX */
		ret = wind_ucs2utf8(bmp, bmplen, ss, NULL);
		if (ret) {
		    free(ss);
		    return ret;
		}
		ss[k] = '\0';
		len = k;
		break;
	    }
	    case choice_DirectoryString_teletexString:
		ss = ds->u.teletexString;
		len = strlen(ss);
		break;
	    case choice_DirectoryString_universalString: {
	        const uint32_t *uni = ds->u.universalString.data;
		size_t unilen = ds->u.universalString.length;
		size_t k;

		ret = wind_ucs4utf8_length(uni, unilen, &k);
		if (ret)
		    return ret;

		ss = malloc(k + 1);
		if (ss == NULL)
		    _hx509_abort("allocation failure"); /* XXX */
		ret = wind_ucs4utf8(uni, unilen, ss, NULL);
		if (ret) {
		    free(ss);
		    return ret;
		}
		ss[k] = '\0';
		len = k;
		break;
	    }
	    default:
		_hx509_abort("unknown directory type: %d", ds->element);
		exit(1);
	    }
	    append_string(str, &total_len, oidname, strlen(oidname), 0);
	    free(oidname);
	    append_string(str, &total_len, "=", 1, 0);
	    append_string(str, &total_len, ss, len, 1);
	    if (ds->element == choice_DirectoryString_bmpString ||
		ds->element == choice_DirectoryString_universalString)
	    {
		free(ss);
	    }
	    if (j + 1 < n->u.rdnSequence.val[i].len)
		append_string(str, &total_len, "+", 1, 0);
	}

	if (i > 0)
	    append_string(str, &total_len, ",", 1, 0);
    }
    return 0;
}