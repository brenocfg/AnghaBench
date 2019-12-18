#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct dict {int dummy; } ;
typedef  int /*<<< orphan*/  sds ;
struct TYPE_12__ {int flags; } ;
typedef  TYPE_2__ redisContext ;
typedef  int /*<<< orphan*/  redisCallbackFn ;
struct TYPE_13__ {int pending_subs; void* privdata; int /*<<< orphan*/ * fn; } ;
typedef  TYPE_3__ redisCallback ;
struct TYPE_11__ {int /*<<< orphan*/  invalid; struct dict* channels; struct dict* patterns; } ;
struct TYPE_14__ {int /*<<< orphan*/  replies; TYPE_1__ sub; TYPE_2__ c; } ;
typedef  TYPE_4__ redisAsyncContext ;
typedef  int /*<<< orphan*/  dictEntry ;

/* Variables and functions */
 int REDIS_DISCONNECTING ; 
 int REDIS_ERR ; 
 int REDIS_FREEING ; 
 int REDIS_MONITORING ; 
 int REDIS_OK ; 
 int REDIS_SUBSCRIBED ; 
 int /*<<< orphan*/  _EL_ADD_WRITE (TYPE_4__*) ; 
 int /*<<< orphan*/  __redisAppendCommand (TYPE_2__*,char const*,size_t) ; 
 int /*<<< orphan*/  __redisPushCallback (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictFind (struct dict*,int /*<<< orphan*/ ) ; 
 TYPE_3__* dictGetEntryVal (int /*<<< orphan*/ *) ; 
 int dictReplace (struct dict*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 char* nextArgument (char const*,char const**,size_t*) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsnewlen (char const*,size_t) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 
 char tolower (char const) ; 

__attribute__((used)) static int __redisAsyncCommand(redisAsyncContext *ac, redisCallbackFn *fn, void *privdata, const char *cmd, size_t len) {
    redisContext *c = &(ac->c);
    redisCallback cb;
    struct dict *cbdict;
    dictEntry *de;
    redisCallback *existcb;
    int pvariant, hasnext;
    const char *cstr, *astr;
    size_t clen, alen;
    const char *p;
    sds sname;
    int ret;

    /* Don't accept new commands when the connection is about to be closed. */
    if (c->flags & (REDIS_DISCONNECTING | REDIS_FREEING)) return REDIS_ERR;

    /* Setup callback */
    cb.fn = fn;
    cb.privdata = privdata;
    cb.pending_subs = 1;

    /* Find out which command will be appended. */
    p = nextArgument(cmd,&cstr,&clen);
    assert(p != NULL);
    hasnext = (p[0] == '$');
    pvariant = (tolower(cstr[0]) == 'p') ? 1 : 0;
    cstr += pvariant;
    clen -= pvariant;

    if (hasnext && strncasecmp(cstr,"subscribe\r\n",11) == 0) {
        c->flags |= REDIS_SUBSCRIBED;

        /* Add every channel/pattern to the list of subscription callbacks. */
        while ((p = nextArgument(p,&astr,&alen)) != NULL) {
            sname = sdsnewlen(astr,alen);
            if (pvariant)
                cbdict = ac->sub.patterns;
            else
                cbdict = ac->sub.channels;

            de = dictFind(cbdict,sname);

            if (de != NULL) {
                existcb = dictGetEntryVal(de);
                cb.pending_subs = existcb->pending_subs + 1;
            }

            ret = dictReplace(cbdict,sname,&cb);

            if (ret == 0) sdsfree(sname);
        }
    } else if (strncasecmp(cstr,"unsubscribe\r\n",13) == 0) {
        /* It is only useful to call (P)UNSUBSCRIBE when the context is
         * subscribed to one or more channels or patterns. */
        if (!(c->flags & REDIS_SUBSCRIBED)) return REDIS_ERR;

        /* (P)UNSUBSCRIBE does not have its own response: every channel or
         * pattern that is unsubscribed will receive a message. This means we
         * should not append a callback function for this command. */
     } else if(strncasecmp(cstr,"monitor\r\n",9) == 0) {
         /* Set monitor flag and push callback */
         c->flags |= REDIS_MONITORING;
         __redisPushCallback(&ac->replies,&cb);
    } else {
        if (c->flags & REDIS_SUBSCRIBED)
            /* This will likely result in an error reply, but it needs to be
             * received and passed to the callback. */
            __redisPushCallback(&ac->sub.invalid,&cb);
        else
            __redisPushCallback(&ac->replies,&cb);
    }

    __redisAppendCommand(c,cmd,len);

    /* Always schedule a write when the write buffer is non-empty */
    _EL_ADD_WRITE(ac);

    return REDIS_OK;
}