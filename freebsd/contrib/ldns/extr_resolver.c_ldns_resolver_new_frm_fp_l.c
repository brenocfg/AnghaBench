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
typedef  int uint8_t ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int int8_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  LDNS_FREE (int) ; 
 int LDNS_MALLOC (int) ; 
 int /*<<< orphan*/  LDNS_MAX_LINELEN ; 
 int /*<<< orphan*/  LDNS_PARSE_NORMAL ; 
 int /*<<< orphan*/  LDNS_PARSE_SKIP_SPACE ; 
 int /*<<< orphan*/  LDNS_RDF_TYPE_A ; 
 int /*<<< orphan*/  LDNS_RDF_TYPE_AAAA ; 
 int /*<<< orphan*/  LDNS_RDF_TYPE_DNAME ; 
#define  LDNS_RESOLV_ANCHOR 134 
#define  LDNS_RESOLV_DEFDOMAIN 133 
#define  LDNS_RESOLV_KEYWORD 132 
 int LDNS_RESOLV_KEYWORDS ; 
#define  LDNS_RESOLV_NAMESERVER 131 
#define  LDNS_RESOLV_OPTIONS 130 
#define  LDNS_RESOLV_SEARCH 129 
#define  LDNS_RESOLV_SORTLIST 128 
 int /*<<< orphan*/  LDNS_STATUS_FILE_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_MEM_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_NULL ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 int /*<<< orphan*/  LDNS_STATUS_SYNTAX_DNAME_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_SYNTAX_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_SYNTAX_MISSING_VALUE_ERR ; 
 int b ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int ldns_bget_token (int,char*,int /*<<< orphan*/ ,size_t) ; 
 int ldns_buffer ; 
 int /*<<< orphan*/  ldns_buffer_free (int) ; 
 int /*<<< orphan*/  ldns_buffer_new_frm_data (int,char*,size_t) ; 
 int /*<<< orphan*/  ldns_buffer_status (int) ; 
 int ldns_fget_token_l (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ldns_rdf_deep_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rdf_new_frm_str (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ldns_read_anchor_file (char*) ; 
 int /*<<< orphan*/  ldns_resolver_deep_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_resolver_new () ; 
 int /*<<< orphan*/  ldns_resolver_push_dnssec_anchor (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_resolver_push_nameserver (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_resolver_push_searchlist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_resolver_set_domain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 

ldns_status
ldns_resolver_new_frm_fp_l(ldns_resolver **res, FILE *fp, int *line_nr)
{
	ldns_resolver *r;
	const char *keyword[LDNS_RESOLV_KEYWORDS];
	char word[LDNS_MAX_LINELEN + 1];
	int8_t expect;
	uint8_t i;
	ldns_rdf *tmp;
#ifdef HAVE_SSL
	ldns_rr *tmp_rr;
#endif
	ssize_t gtr, bgtr;
	ldns_buffer *b;
        int lnr = 0, oldline;
	FILE* myfp = fp;
        if(!line_nr) line_nr = &lnr;

	if(!fp) {
		myfp = fopen("/etc/resolv.conf", "r");
		if(!myfp)
			return LDNS_STATUS_FILE_ERR;
	}

	/* do this better
	 * expect =
	 * 0: keyword
	 * 1: default domain dname
	 * 2: NS aaaa or a record
	 */

	/* recognized keywords */
	keyword[LDNS_RESOLV_NAMESERVER] = "nameserver";
	keyword[LDNS_RESOLV_DEFDOMAIN] = "domain";
	keyword[LDNS_RESOLV_SEARCH] = "search";
	/* these two are read but not used atm TODO */
	keyword[LDNS_RESOLV_SORTLIST] = "sortlist";
	keyword[LDNS_RESOLV_OPTIONS] = "options";
	keyword[LDNS_RESOLV_ANCHOR] = "anchor";
	expect = LDNS_RESOLV_KEYWORD;

	r = ldns_resolver_new();
	if (!r) {
		if(!fp) fclose(myfp);
		return LDNS_STATUS_MEM_ERR;
	}

	gtr = 1;
	word[0] = 0;
        oldline = *line_nr;
        expect = LDNS_RESOLV_KEYWORD;
	while (gtr > 0) {
		/* check comments */
		if (word[0] == '#') {
                        word[0]='x';
                        if(oldline == *line_nr) {
                                /* skip until end of line */
                                int c;
                                do {
                                        c = fgetc(myfp);
                                } while(c != EOF && c != '\n');
                                if(c=='\n') (*line_nr)++;
                        }
			/* and read next to prepare for further parsing */
                        oldline = *line_nr;
			continue;
		}
                oldline = *line_nr;
		switch(expect) {
			case LDNS_RESOLV_KEYWORD:
				/* keyword */
				gtr = ldns_fget_token_l(myfp, word, LDNS_PARSE_NORMAL, 0, line_nr);
				if (gtr != 0) {
                                        if(word[0] == '#') continue;
					for(i = 0; i < LDNS_RESOLV_KEYWORDS; i++) {
						if (strcasecmp(keyword[i], word) == 0) {
							/* chosen the keyword and
							 * expect values carefully
	        					 */
							expect = i;
							break;
						}
					}
					/* no keyword recognized */
					if (expect == LDNS_RESOLV_KEYWORD) {
						/* skip line */
						/*
						ldns_resolver_deep_free(r);
						if(!fp) fclose(myfp);
						return LDNS_STATUS_SYNTAX_KEYWORD_ERR;
						*/
					}
				}
				break;
			case LDNS_RESOLV_DEFDOMAIN:
				/* default domain dname */
				gtr = ldns_fget_token_l(myfp, word, LDNS_PARSE_NORMAL, 0, line_nr);
				if (gtr == 0) {
					if(!fp) fclose(myfp);
					return LDNS_STATUS_SYNTAX_MISSING_VALUE_ERR;
				}
                                if(word[0] == '#') {
                                        expect = LDNS_RESOLV_KEYWORD;
                                        continue;
                                }
				tmp = ldns_rdf_new_frm_str(LDNS_RDF_TYPE_DNAME, word);
				if (!tmp) {
					ldns_resolver_deep_free(r);
					if(!fp) fclose(myfp);
					return LDNS_STATUS_SYNTAX_DNAME_ERR;
				}

				/* DOn't free, because we copy the pointer */
				ldns_resolver_set_domain(r, tmp);
				expect = LDNS_RESOLV_KEYWORD;
				break;
			case LDNS_RESOLV_NAMESERVER:
				/* NS aaaa or a record */
				gtr = ldns_fget_token_l(myfp, word, LDNS_PARSE_NORMAL, 0, line_nr);
				if (gtr == 0) {
					if(!fp) fclose(myfp);
					return LDNS_STATUS_SYNTAX_MISSING_VALUE_ERR;
				}
                                if(word[0] == '#') {
                                        expect = LDNS_RESOLV_KEYWORD;
                                        continue;
                                }
                                if(strchr(word, '%')) {
                                        /* snip off interface labels,
                                         * fe80::222:19ff:fe31:4222%eth0 */
                                        strchr(word, '%')[0]=0;
                                }
				tmp = ldns_rdf_new_frm_str(LDNS_RDF_TYPE_AAAA, word);
				if (!tmp) {
					/* try ip4 */
					tmp = ldns_rdf_new_frm_str(LDNS_RDF_TYPE_A, word);
				}
				/* could not parse it, exit */
				if (!tmp) {
					ldns_resolver_deep_free(r);
					if(!fp) fclose(myfp);
					return LDNS_STATUS_SYNTAX_ERR;
				}
				(void)ldns_resolver_push_nameserver(r, tmp);
				ldns_rdf_deep_free(tmp);
				expect = LDNS_RESOLV_KEYWORD;
				break;
			case LDNS_RESOLV_SEARCH:
				/* search list domain dname */
				gtr = ldns_fget_token_l(myfp, word, LDNS_PARSE_SKIP_SPACE, 0, line_nr);
				b = LDNS_MALLOC(ldns_buffer);
				if(!b) {
					ldns_resolver_deep_free(r);
					if(!fp) fclose(myfp);
					return LDNS_STATUS_MEM_ERR;
				}

				ldns_buffer_new_frm_data(b, word, (size_t) gtr);
				if(ldns_buffer_status(b) != LDNS_STATUS_OK) {
					LDNS_FREE(b);
					ldns_resolver_deep_free(r);
					if(!fp) fclose(myfp);
					return LDNS_STATUS_MEM_ERR;
				}
				bgtr = ldns_bget_token(b, word, LDNS_PARSE_NORMAL, (size_t) gtr + 1);
				while (bgtr > 0) {
					gtr -= bgtr;
                                        if(word[0] == '#') {
                                                expect = LDNS_RESOLV_KEYWORD;
                                                break;
                                        }
					tmp = ldns_rdf_new_frm_str(LDNS_RDF_TYPE_DNAME, word);
					if (!tmp) {
						ldns_resolver_deep_free(r);
						ldns_buffer_free(b);
						if(!fp) fclose(myfp);
						return LDNS_STATUS_SYNTAX_DNAME_ERR;
					}

					ldns_resolver_push_searchlist(r, tmp);

					ldns_rdf_deep_free(tmp);
					bgtr = ldns_bget_token(b, word, LDNS_PARSE_NORMAL,
					    (size_t) gtr + 1);
				}
				ldns_buffer_free(b);
				if (expect != LDNS_RESOLV_KEYWORD) {
					gtr = 1;
					expect = LDNS_RESOLV_KEYWORD;
				}
				break;
			case LDNS_RESOLV_SORTLIST:
				gtr = ldns_fget_token_l(myfp, word, LDNS_PARSE_SKIP_SPACE, 0, line_nr);
				/* sortlist not implemented atm */
				expect = LDNS_RESOLV_KEYWORD;
				break;
			case LDNS_RESOLV_OPTIONS:
				gtr = ldns_fget_token_l(myfp, word, LDNS_PARSE_SKIP_SPACE, 0, line_nr);
				/* options not implemented atm */
				expect = LDNS_RESOLV_KEYWORD;
				break;
			case LDNS_RESOLV_ANCHOR:
				/* a file containing a DNSSEC trust anchor */
				gtr = ldns_fget_token_l(myfp, word, LDNS_PARSE_NORMAL, 0, line_nr);
				if (gtr == 0) {
					ldns_resolver_deep_free(r);
					if(!fp) fclose(myfp);
					return LDNS_STATUS_SYNTAX_MISSING_VALUE_ERR;
				}
                                if(word[0] == '#') {
                                        expect = LDNS_RESOLV_KEYWORD;
                                        continue;
                                }

#ifdef HAVE_SSL
				tmp_rr = ldns_read_anchor_file(word);
				(void) ldns_resolver_push_dnssec_anchor(r, tmp_rr);
				ldns_rr_free(tmp_rr);
#endif
				expect = LDNS_RESOLV_KEYWORD;
				break;
		}
	}

	if(!fp)
		fclose(myfp);

	if (res) {
		*res = r;
		return LDNS_STATUS_OK;
	} else {
		ldns_resolver_deep_free(r);
		return LDNS_STATUS_NULL;
	}
}