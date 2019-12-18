#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* member_0; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ GEnum ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  BROWSERS ; 
 int /*<<< orphan*/  GEO_LOCATION ; 
 int /*<<< orphan*/  HOSTS ; 
 int /*<<< orphan*/  KEYPHRASES ; 
 int /*<<< orphan*/  NOT_FOUND ; 
 int /*<<< orphan*/  OS ; 
 int /*<<< orphan*/  REFERRERS ; 
 int /*<<< orphan*/  REFERRING_SITES ; 
 int /*<<< orphan*/  REMOTE_USER ; 
 int /*<<< orphan*/  REQUESTS ; 
 int /*<<< orphan*/  REQUESTS_STATIC ; 
 int /*<<< orphan*/  STATUS_CODES ; 
 int /*<<< orphan*/  VIRTUAL_HOSTS ; 
 int /*<<< orphan*/  VISITORS ; 
 int /*<<< orphan*/  VISIT_TIMES ; 
 int str2enum (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 

int
get_module_enum (const char *str)
{
  /* *INDENT-OFF* */
  /* String modules to enumerated modules */
  GEnum enum_modules[] = {
    {"VISITORS"        , VISITORS}        ,
    {"REQUESTS"        , REQUESTS}        ,
    {"REQUESTS_STATIC" , REQUESTS_STATIC} ,
    {"NOT_FOUND"       , NOT_FOUND}       ,
    {"HOSTS"           , HOSTS}           ,
    {"OS"              , OS}              ,
    {"BROWSERS"        , BROWSERS}        ,
    {"VISIT_TIMES"     , VISIT_TIMES}     ,
    {"VIRTUAL_HOSTS"   , VIRTUAL_HOSTS}   ,
    {"REFERRERS"       , REFERRERS}       ,
    {"REFERRING_SITES" , REFERRING_SITES} ,
    {"KEYPHRASES"      , KEYPHRASES}      ,
    {"STATUS_CODES"    , STATUS_CODES}    ,
    {"REMOTE_USER"     , REMOTE_USER}     ,
#ifdef HAVE_GEOLOCATION
    {"GEO_LOCATION"    , GEO_LOCATION}    ,
#endif
  };
  /* *INDENT-ON* */

  return str2enum (enum_modules, ARRAY_SIZE (enum_modules), str);
}