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
typedef  int (* hx509_pem_read_func ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,void*,size_t,void*) ;
typedef  int /*<<< orphan*/  hx509_pem_header ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int HX509_PARSING_KEY_FAILED ; 
 int /*<<< orphan*/  abort () ; 
 int base64_decode (char*,char*) ; 
 char* emalloc (int) ; 
 void* erealloc (void*,size_t) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int hx509_pem_add_header (int /*<<< orphan*/ **,char*,char*) ; 
 int /*<<< orphan*/  hx509_pem_free_header (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  isspace (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* strchr (char*,char) ; 
 int strcspn (char*,char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,void*,size_t,void*) ; 

int
hx509_pem_read(hx509_context context,
	       FILE *f,
	       hx509_pem_read_func func,
	       void *ctx)
{
    hx509_pem_header *headers = NULL;
    char *type = NULL;
    void *data = NULL;
    size_t len = 0;
    char buf[1024];
    int ret = HX509_PARSING_KEY_FAILED;

    enum { BEFORE, SEARCHHEADER, INHEADER, INDATA, DONE } where;

    where = BEFORE;

    while (fgets(buf, sizeof(buf), f) != NULL) {
	char *p;
	int i;

	i = strcspn(buf, "\n");
	if (buf[i] == '\n') {
	    buf[i] = '\0';
	    if (i > 0)
		i--;
	}
	if (buf[i] == '\r') {
	    buf[i] = '\0';
	    if (i > 0)
		i--;
	}

	switch (where) {
	case BEFORE:
	    if (strncmp("-----BEGIN ", buf, 11) == 0) {
		type = strdup(buf + 11);
		if (type == NULL)
		    break;
		p = strchr(type, '-');
		if (p)
		    *p = '\0';
		where = SEARCHHEADER;
	    }
	    break;
	case SEARCHHEADER:
	    p = strchr(buf, ':');
	    if (p == NULL) {
		where = INDATA;
		goto indata;
	    }
	    /* FALLTHOUGH */
	case INHEADER:
	    if (buf[0] == '\0') {
		where = INDATA;
		break;
	    }
	    p = strchr(buf, ':');
	    if (p) {
		*p++ = '\0';
		while (isspace((int)*p))
		    p++;
		ret = hx509_pem_add_header(&headers, buf, p);
		if (ret)
		    abort();
	    }
	    break;
	case INDATA:
	indata:

	    if (strncmp("-----END ", buf, 9) == 0) {
		where = DONE;
		break;
	    }

	    p = emalloc(i);
	    i = base64_decode(buf, p);
	    if (i < 0) {
		free(p);
		goto out;
	    }

	    data = erealloc(data, len + i);
	    memcpy(((char *)data) + len, p, i);
	    free(p);
	    len += i;
	    break;
	case DONE:
	    abort();
	}

	if (where == DONE) {
	    ret = (*func)(context, type, headers, data, len, ctx);
	out:
	    free(data);
	    data = NULL;
	    len = 0;
	    free(type);
	    type = NULL;
	    where = BEFORE;
	    hx509_pem_free_header(headers);
	    headers = NULL;
	    if (ret)
		break;
	}
    }

    if (where != BEFORE) {
	hx509_set_error_string(context, 0, HX509_PARSING_KEY_FAILED,
			       "File ends before end of PEM end tag");
	ret = HX509_PARSING_KEY_FAILED;
    }
    if (data)
	free(data);
    if (type)
	free(type);
    if (headers)
	hx509_pem_free_header(headers);

    return ret;
}