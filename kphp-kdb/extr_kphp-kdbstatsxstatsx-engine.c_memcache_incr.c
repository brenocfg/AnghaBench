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
struct connection {int /*<<< orphan*/  Out; } ;
typedef  int /*<<< orphan*/  region ;
typedef  int /*<<< orphan*/  country ;

/* Variables and functions */
 int char3_to_int (char*) ; 
 int counter_incr (long long,int,int /*<<< orphan*/ ,int,int) ; 
 int counter_incr_ext (long long,int,int /*<<< orphan*/ ,int,int,char,char,char,char,char,int,int,int,char) ; 
 scalar_t__ custom_version_names ; 
 int /*<<< orphan*/  debug_error (char*,char*,char const*,int) ; 
 int /*<<< orphan*/  debug_key (char const*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int get_at_prefix_length (char const*,int) ; 
 long long incr_counter_id ; 
 int incr_version ; 
 scalar_t__ incr_version_read ; 
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int not_found (struct connection*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*,char*,char*,char*) ; 
 int /*<<< orphan*/  stats_buff ; 
 int /*<<< orphan*/  stderr ; 
 long long strtol (char*,char**,int) ; 
 long long strtoll (char const*,char**,int) ; 
 int verbosity ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int memcache_incr (struct connection *c, int op, const char *key, int len, long long arg) {
  if (verbosity >= 4) {
    fprintf (stderr, "memcache_incr (op = %d, key = \"", op);
    debug_key (key, len);
    fprintf (stderr, "\")\n");
  }

  const int dog_len = get_at_prefix_length (key, len);
  key += dog_len;
  len -= dog_len;

  if (len >= 7 && !memcmp (key, "counter", 7)) {
    long long cnt_id, tmp;
    int  subcnt_id=-1,  uid, city = 0, res;
    char sex = 0, age = 0, status = 0, polit = 0, section = 0, region[4], country[4], source = 0, *p;
    char optional_params_is_given = 1;
    int version = -1;
    memset (region, 0, sizeof (region));
    memset (country, 0, sizeof (country));
    errno = 0; tmp = strtoll (key + 7, &p, 10);
    if (errno) {
      debug_error ("incr", "fail to parse counter_id", key, len);
      return not_found (c);
    }
    cnt_id = tmp;
    if (*p == '@') {
      errno = 0; tmp = strtol(p + 1, &p, 10);
      if (errno || tmp < 0) {
        debug_error ("incr", "fail to parse version",  key, len);
        return not_found (c);
      }
      if (verbosity >= 3) {
        fprintf (stderr, "version = %d\n", version);
      }
      version = (int) tmp;
    }
    if (*p == ':') {
      errno = 0; tmp = strtol(p+1, &p, 10);
      if (errno) {
        debug_error ("incr", "fail to parse subcnt_id",  key, len);
        return not_found (c);
      }
      subcnt_id = (int) tmp;
    }
    if (*p != '#') {
      debug_error ("incr", "missed uid (expected '#')", key, len);
      return not_found (c);
    }
    errno = 0; tmp = strtol (p+1, &p, 10);
    if (errno) {
      debug_error ("incr", "fail to parse uid", key, len);
      return not_found (c);
    }
    uid = (int) tmp;
    if (*p && *p != '#') {
      debug_error ("incr", "expected '#' after uid", key, len);
      return not_found (c);
    }
    if (verbosity >= 4) {
      fprintf (stderr, "incr (cnt_id = %lld, subcnt_id = %d, uid = %d)\n", cnt_id, subcnt_id, uid);
    }
    if (!(*p)) optional_params_is_given = 0;
    if (*p) p++;
    if (*p) sex = *p++;
    if (*p) age = *p++;
    if (*p) status = *p++;
    if (*p) polit = *p++;
    if (*p) section = *p++;
    if (*p == ';') {
      sscanf (p+1,"%d;%3[^;];%3[^;];%c", &city, region, country, &source);
    }
    if (sex > '0' && sex <= '2') { sex -= '0'; } else { sex = 0; }
    if (age > '0' && age <= '8') { age -= '0'; } else { age = 0; }
    if (status > '0' && status <= '8') { status -= '0'; } else { status = 0; }
    if (polit > '0' && polit <= '8') { polit -= '0'; } else { polit = 0; }
    if (section >= 'A' && section <= 'P') { section -= 'A' - 1; } else { section = 0; }
    if (source >= 'A' && source <= 'P') { source -= 'A' - 1; } else { source = 0; }
    if (verbosity >= 4) {
      fprintf (stderr, "optional_params_is_given = %d\n", optional_params_is_given);
      fprintf (stderr, "sex = %d, age = %d, status = %d, polit = %d, section = %d, city = %d, region = %d, country = %d, source = %d\n",
             sex, age, status, polit, section, city, char3_to_int(region), char3_to_int(country),(int) source);
    }
    //int counter_incr_ext (int counter_id, int user_id, int replaying, int op, int subcnt, int sex, int age, int m_status, int polit_views, int section, int city, int country, int geoip_country, int source);
    incr_version = version;
    incr_counter_id = cnt_id;
    incr_version_read = 0;
    if ((version >= 0 && !custom_version_names) || (version < 0 && custom_version_names)) {
      debug_error ("incr", "fail due to version",  key, len);
      return not_found (c);
    }
    res = (optional_params_is_given && subcnt_id == -1) ?
           counter_incr_ext (cnt_id, uid, 0, op, subcnt_id, sex, age, status, polit, section, city, char3_to_int(region), char3_to_int(country), source) :
           counter_incr (cnt_id, uid, 0, op, subcnt_id);
    //int counter_incr (int counter_id, int user_id, int replaying, int op, int subcnt);
    if (res < 0) return not_found (c);
    write_out (&c->Out, stats_buff, sprintf (stats_buff, "%d\r\n", res));
    return 0;
  }
  return not_found (c);
}