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
typedef  char u_int8_t ;
struct universe {int /*<<< orphan*/ * hash; } ;
struct option_data {char* data; unsigned int len; } ;
struct option {char* format; size_t code; } ;
struct iaddr {unsigned int len; char* iabuf; } ;
typedef  int /*<<< orphan*/  hunkbuf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int COMMA ; 
 int DOT ; 
 int NUMBER ; 
 int SEMI ; 
 int STRING ; 
 int /*<<< orphan*/  convert_num (char*,char*,int /*<<< orphan*/ ,int) ; 
 struct universe dhcp_universe ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ hash_lookup (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_identifier (int) ; 
 char* malloc (unsigned int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 
 int next_token (char**,int /*<<< orphan*/ *) ; 
 unsigned int parse_X (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  parse_ip_addr (int /*<<< orphan*/ *,struct iaddr*) ; 
 int /*<<< orphan*/  parse_warn (char*,...) ; 
 int peek_token (char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_to_semi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 char* strdup (char*) ; 
 unsigned int strlen (char*) ; 
 int /*<<< orphan*/  universe_hash ; 
 int /*<<< orphan*/  warning (char*,char const) ; 

struct option *
parse_option_decl(FILE *cfile, struct option_data *options)
{
	char		*val;
	int		 token;
	u_int8_t	 buf[4];
	u_int8_t	 hunkbuf[1024];
	unsigned	 hunkix = 0;
	char		*vendor;
	const char	*fmt;
	struct universe	*universe;
	struct option	*option;
	struct iaddr	 ip_addr;
	u_int8_t	*dp;
	unsigned	 len;
	int		 nul_term = 0;

	token = next_token(&val, cfile);
	if (!is_identifier(token)) {
		parse_warn("expecting identifier after option keyword.");
		if (token != SEMI)
			skip_to_semi(cfile);
		return (NULL);
	}
	if ((vendor = strdup(val)) == NULL)
		error("no memory for vendor information.");

	token = peek_token(&val, cfile);
	if (token == DOT) {
		/* Go ahead and take the DOT token... */
		token = next_token(&val, cfile);

		/* The next token should be an identifier... */
		token = next_token(&val, cfile);
		if (!is_identifier(token)) {
			parse_warn("expecting identifier after '.'");
			if (token != SEMI)
				skip_to_semi(cfile);
			free(vendor);
			return (NULL);
		}

		/* Look up the option name hash table for the specified
		   vendor. */
		universe = ((struct universe *)hash_lookup(&universe_hash,
		    (unsigned char *)vendor, 0));
		/* If it's not there, we can't parse the rest of the
		   declaration. */
		if (!universe) {
			parse_warn("no vendor named %s.", vendor);
			skip_to_semi(cfile);
			free(vendor);
			return (NULL);
		}
	} else {
		/* Use the default hash table, which contains all the
		   standard dhcp option names. */
		val = vendor;
		universe = &dhcp_universe;
	}

	/* Look up the actual option info... */
	option = (struct option *)hash_lookup(universe->hash,
	    (unsigned char *)val, 0);

	/* If we didn't get an option structure, it's an undefined option. */
	if (!option) {
		if (val == vendor)
			parse_warn("no option named %s", val);
		else
			parse_warn("no option named %s for vendor %s",
				    val, vendor);
		skip_to_semi(cfile);
		free(vendor);
		return (NULL);
	}

	/* Free the initial identifier token. */
	free(vendor);

	/* Parse the option data... */
	do {
		for (fmt = option->format; *fmt; fmt++) {
			if (*fmt == 'A')
				break;
			switch (*fmt) {
			case 'X':
				len = parse_X(cfile, &hunkbuf[hunkix],
				    sizeof(hunkbuf) - hunkix);
				hunkix += len;
				break;
			case 't': /* Text string... */
				token = next_token(&val, cfile);
				if (token != STRING) {
					parse_warn("expecting string.");
					skip_to_semi(cfile);
					return (NULL);
				}
				len = strlen(val);
				if (hunkix + len + 1 > sizeof(hunkbuf)) {
					parse_warn("option data buffer %s",
					    "overflow");
					skip_to_semi(cfile);
					return (NULL);
				}
				memcpy(&hunkbuf[hunkix], val, len + 1);
				nul_term = 1;
				hunkix += len;
				break;
			case 'I': /* IP address. */
				if (!parse_ip_addr(cfile, &ip_addr))
					return (NULL);
				len = ip_addr.len;
				dp = ip_addr.iabuf;
alloc:
				if (hunkix + len > sizeof(hunkbuf)) {
					parse_warn("option data buffer "
					    "overflow");
					skip_to_semi(cfile);
					return (NULL);
				}
				memcpy(&hunkbuf[hunkix], dp, len);
				hunkix += len;
				break;
			case 'L':	/* Unsigned 32-bit integer... */
			case 'l':	/* Signed 32-bit integer... */
				token = next_token(&val, cfile);
				if (token != NUMBER) {
need_number:
					parse_warn("expecting number.");
					if (token != SEMI)
						skip_to_semi(cfile);
					return (NULL);
				}
				convert_num(buf, val, 0, 32);
				len = 4;
				dp = buf;
				goto alloc;
			case 's':	/* Signed 16-bit integer. */
			case 'S':	/* Unsigned 16-bit integer. */
				token = next_token(&val, cfile);
				if (token != NUMBER)
					goto need_number;
				convert_num(buf, val, 0, 16);
				len = 2;
				dp = buf;
				goto alloc;
			case 'b':	/* Signed 8-bit integer. */
			case 'B':	/* Unsigned 8-bit integer. */
				token = next_token(&val, cfile);
				if (token != NUMBER)
					goto need_number;
				convert_num(buf, val, 0, 8);
				len = 1;
				dp = buf;
				goto alloc;
			case 'f': /* Boolean flag. */
				token = next_token(&val, cfile);
				if (!is_identifier(token)) {
					parse_warn("expecting identifier.");
bad_flag:
					if (token != SEMI)
						skip_to_semi(cfile);
					return (NULL);
				}
				if (!strcasecmp(val, "true") ||
				    !strcasecmp(val, "on"))
					buf[0] = 1;
				else if (!strcasecmp(val, "false") ||
				    !strcasecmp(val, "off"))
					buf[0] = 0;
				else {
					parse_warn("expecting boolean.");
					goto bad_flag;
				}
				len = 1;
				dp = buf;
				goto alloc;
			default:
				warning("Bad format %c in parse_option_param.",
				    *fmt);
				skip_to_semi(cfile);
				return (NULL);
			}
		}
		token = next_token(&val, cfile);
	} while (*fmt == 'A' && token == COMMA);

	if (token != SEMI) {
		parse_warn("semicolon expected.");
		skip_to_semi(cfile);
		return (NULL);
	}

	options[option->code].data = malloc(hunkix + nul_term);
	if (!options[option->code].data)
		error("out of memory allocating option data.");
	memcpy(options[option->code].data, hunkbuf, hunkix + nul_term);
	options[option->code].len = hunkix;
	return (option);
}